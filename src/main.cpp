#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "kv.h"
#include "stringutils.h"
using namespace std;

void check_kv_in_namespace(map<string, KeyValue> &namespaces, string nm) {
  if (namespaces.count(nm) == 0) {
    namespaces[nm] = KeyValue();
  }
}
vector<string> get_namespace_and_key(string vec) {
  vector<string> nms;
  string nm;
  string key;
  nms = splitString(vec, ":");
  if (nms.size() > 1) {
    nm = nms[0];
    key = nms[1];
  } else {
    nm = "default";
    key = nms[0];
  }
  return {nm,key};
}

int main() {
  map<string,KeyValue> namespaces;
  string line;
  vector<string> keyvalue;
  enum kvAction {GET, SET, DELETE, LIST};
  map<string, kvAction> actionMap;
  kvAction action;
  string msg;
  vector<string> nms;
  string nm;

  actionMap["get"] = GET;
  actionMap["set"] = SET;
  actionMap["delete"] = DELETE;
  actionMap["list"] = LIST;

  while (getline (cin, line)) {
    keyvalue = splitString(line);
    action = actionMap[keyvalue[0]];
    switch(action) {
      case GET:
        nms = get_namespace_and_key(keyvalue[1]);
        check_kv_in_namespace(namespaces, nms[0]);
        msg = namespaces[nms[0]].get_key(nms[1]);
        break;
      case SET:
        nms = get_namespace_and_key(keyvalue[1]);
        check_kv_in_namespace(namespaces, nms[0]);
        msg = namespaces[nms[0]].set_key(nms[1], keyvalue[2]);
        break;
      case DELETE:
        nms = get_namespace_and_key(keyvalue[1]);
        check_kv_in_namespace(namespaces, nms[0]);
        msg = namespaces[nms[0]].delete_key(nms[1]);
        break;
      case LIST:
        nm = keyvalue.size() > 1 ? keyvalue[1] : "default";
        cout << "namespace: " << nm << "\n";
        msg = namespaces[nm].list_keys();
    }
    cout << msg << "\n";
  }

  return 0;
}
