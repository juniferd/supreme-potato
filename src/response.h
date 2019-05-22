#ifndef RESPONSE_H
#define RESPONSE_H
#include "responseenums.h"
#include <string>
using namespace std;
class Response {
private:
  int status_code;
  string status_message;
  string body;
public:
  string get_response();
  Response(responseType type, string opt_body="");
};
#endif
