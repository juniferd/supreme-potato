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
  enum kvAction {GET, SET, DELETE};
  map<string, kvAction> actionMap;
  kvAction action;
  string msg;

  actionMap["get"] = GET;
  actionMap["set"] = SET;
  actionMap["delete"] = DELETE;

  while (getline (cin, line)) {
    keyvalue = splitString(line);
    action = actionMap[keyvalue[0]];
    switch(action) {
      case GET:
        msg = getKey(kv, keyvalue[1]);
        break;
      case SET:
        msg = setKey(kv, keyvalue[1], keyvalue[2]);
        break;
      case DELETE:
        msg = deleteKey(kv, keyvalue[1]);
        break;
    }
    cout << msg << "\n";
  }

  return 0;
}
