#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <string>
#include <map>
#include <vector>

#define PORT 8888

#define MAXLEN (1024*32)

#define vector std::vector
#define string std::string
#define map std::map

class KVServer {

  private:
    int master_socket, client_socket[30], max_clients = 30;
    struct sockaddr_in address;
    fd_set readfds;
    char buffer[MAXLEN];
    map<int, vector<string>> buffers;
    int addrlen = sizeof(address);

    void handle_read(int sd, char *buffer, int valread) {
      //set the string terminating NULL byte on the end of the data read
      buffer[valread] = '\0';
      char *cpy = buffer;
      char *c = index(cpy, '\n');
      int remaining = valread;

      while (c != NULL) {
        int length = c - cpy;
        char buf[length+1];
        strncpy(buf, cpy, length);
        buf[length] = '\0';
        buffers[sd].push_back(string(buf));

        handle_buffers(buffers[sd]);
        buffers[sd].clear();

        remaining -= (length+1);
        cpy = c+1;
        c = index(cpy, '\n');
      }

      if (remaining > 0) {
        string s = string(cpy);
        if (cpy != "") {
          buffers[sd].push_back(string(cpy));
        }
      }
    }

    void strip_trailing_whitespace(string &line) {
      int i = line.size();
      while (--i >= 0) {
        if (line[i] == '\r' || line[i] == '\n' || line[i] == ' ' || line[i] == '\t') {
          line[i] = '\0';
        } else {
          return;
        }
      }
    }

    void handle_line(string line) {
      strip_trailing_whitespace(line);
      printf("HANDLING LINE: '%s'\n", line.c_str());
    }

    void handle_buffers(vector<string> &buf) {
      int count = 0;
      for (int i = 0; i < buf.size(); i++) {
        count += buf[i].size();
      }

      char cpy[count+1];
      cpy[count] = '\0';

      int start = 0;
      for (int i = 0; i < buf.size(); i++) {
        strncpy(cpy + start, buf[i].c_str(), buf[i].size());
        start += buf[i].size();
      }

      handle_line(cpy);
    }

    void clear_buffers(int sd) {

      auto it = buffers.find(sd);
      if (it != buffers.end()) {
        buffers.erase(it);
      }

    }

  public:
    void init() {
      int opt = true;
      memset(client_socket, 0, max_clients * sizeof(client_socket[0]));

      if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
          perror("socket failed");
          exit(EXIT_FAILURE);
      }

      // set master socket to allow multiple connections,
      // this is just a good habit, it will work without this
      if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
            sizeof(opt)) < 0) {
          perror("setsockopt");
          exit(EXIT_FAILURE);
      }

      address.sin_family = AF_INET;
      address.sin_addr.s_addr = INADDR_ANY;
      address.sin_port = htons(PORT);

      //bind the socket to localhost port 8888
      if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
          perror("bind failed");
          exit(EXIT_FAILURE);
      }
      printf("Listening on port %d \n", PORT);

      // try to specify maximum of 3 pending connections for the master socket
      if (listen(master_socket, 3) < 0) {
          perror("listen");
          exit(EXIT_FAILURE);
      }

      puts("Waiting for connections ...");
    }

    void add_new_socket(int new_socket) {
      string welcome = "KV Daemon 0.1 \r\n";

      //inform user of socket number - used in send and receive commands
      printf("New connection, socket fd is %d, ip is : %s, port : %d \n",
        new_socket, inet_ntoa(address.sin_addr), ntohs (address.sin_port));

      int sent = send(new_socket, welcome.c_str(), strlen(welcome.c_str()), 0);
      if (sent != strlen(welcome.c_str())) {
          perror("send");
      }

      puts("Welcome message sent successfully");

      //add new socket to array of sockets
      for (int i = 0; i < max_clients; i++) {
          //if position is empty
          if (client_socket[i] == 0) {
              client_socket[i] = new_socket;
              printf("Adding to list of sockets as %d\n", i);

              break;
          }
      }
    }

    void read_from_sockets() {
      int sd, valread;

      //else its some IO operation on some other socket
      for (int i = 0; i < max_clients; i++) {
          sd = client_socket[i];

          if (FD_ISSET(sd, &readfds)) {
              //Check if it was for closing, and also read the incoming message
              if ((valread = read(sd, buffer, MAXLEN)) == 0) {
                  clear_buffers(sd);

                  getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                  printf("Host disconnected, ip %s, port %d \n",
                        inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                  close(sd);
                  client_socket[i] = 0;
              } else {
                  handle_read(sd, buffer, valread);
              }
          }
      }
    }

    void main_loop() {
      int max_sd, new_socket, sd;
      struct sockaddr_in address;

      while(true) {
          //clear the socket set
          FD_ZERO(&readfds);

          //add master socket to set
          FD_SET(master_socket, &readfds);
          max_sd = master_socket;

          //add child sockets to set
          for (int i = 0 ; i < max_clients ; i++) {
              sd = client_socket[i];

              //if valid socket descriptor then add to read list
              if (sd > 0) FD_SET(sd, &readfds);

              //highest file descriptor number, need it for the select function
              if (sd > max_sd) max_sd = sd;
          }

          //wait for an activity on one of the sockets, timeout is NULL, so wait indefinitely
          int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

          if ((activity < 0) && (errno!=EINTR)) {
              printf("select error");
          }

          //If something happened on the master socket,
          //then its an incoming connection
          if (FD_ISSET(master_socket, &readfds)) {
              if ((new_socket = accept(master_socket,
                      (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
                  perror("accept");
                  exit(EXIT_FAILURE);
              }

              add_new_socket(new_socket);
          }

          read_from_sockets();

      }


    }
};

int main(int argc , char *argv[]) {
    KVServer kv = KVServer();
    kv.init();
    kv.main_loop();
    return 0;
}
