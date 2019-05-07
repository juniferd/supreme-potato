#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "kv.h"
#include "stringutils.h"
using namespace std;

int main() {
  map<string, string> kv;
  string line;
  vector<string> keyvalue;
  enum kvAction {GET, SET, DELETE, LIST};
  map<string, kvAction> actionMap;
  kvAction action;
  string msg;

  actionMap["get"] = GET;
  actionMap["set"] = SET;
  actionMap["delete"] = DELETE;
  actionMap["list"] = LIST;

  while (getline (cin, line)) {
    keyvalue = splitString(line);
    action = actionMap[keyvalue[0]];
    switch(action) {
      case GET:
        msg = kv::getKey(kv, keyvalue[1]);
        break;
      case SET:
        msg = kv::setKey(kv, keyvalue[1], keyvalue[2]);
        break;
      case DELETE:
        msg = kv::deleteKey(kv, keyvalue[1]);
        break;
      case LIST:
        msg = kv::listKeys(kv);
    }
    cout << msg << "\n";
  }

  return 0;
}
