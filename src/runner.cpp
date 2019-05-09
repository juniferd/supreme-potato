#include "runner.h"
#include "stringutils.h"
#include "enums.h"
void MainRunner::check_kv_in_namespace(map<string, KeyValue> &namespaces, string nm) {
  if (namespaces.count(nm) == 0) {
    namespaces[nm] = KeyValue();
  }
}

vector<string> MainRunner::get_namespace_and_key(string vec) {
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

string MainRunner::handle_line(string line){
  string msg;
  vector<string> keyvalue;
  kvAction action;
  vector<string> nms;
  string nm;
  keyvalue = splitString(line);

  for (auto s : keyvalue)
    cout << "'" << s << "' (" << s.size() << ") ";
  cout << endl;
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
      //msg = "namespace: " + nm + "\n";
      msg = namespaces[nm].list_keys();
  }
  msg = msg + "\n";
  cout << msg;
  return msg;
}
