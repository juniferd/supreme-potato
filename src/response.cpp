#include "response.h"

Response::Response(responseType type, string opt_body) {
  body = opt_body;
  if (type == SUCCESS) {
    status_code = 200;
    status_message = "OK";
  } else {
    status_code = 400;
    status_message = "Bad Request";
  }
}

string Response::get_response() {
  string resp;
  resp = to_string(status_code ) + " " + status_message;
  resp += "\n" + body + "\n";
  resp += "---\n";
  return resp;
}
