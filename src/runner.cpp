#include "runner.h"
#include "stringutils.h"
#include "enums.h"
string MainRunner::set_namespace(map<string,KeyValue> &namespaces, string nm) {
  string msg;
  if (namespaces.count(nm) == 0) {
    namespaces[nm] = KeyValue();
    msg = "New namespace created: " + nm;
  } else {
    msg = nm + " already exists as a namespace";
  }
  return msg + "\n";
}

string MainRunner::delete_namespace(map<string,KeyValue> &namespaces, string nm) {
  string msg;
  if (namespaces.count(nm) > 0) {
    namespaces.erase(nm);
    msg = nm + " deleted as a namespace";
  } else {
    msg = nm + " does not exist as a namespace";
  }
  return msg + "\n";
}

tuple<string,string> MainRunner::get_namespace_and_key(string vec) {
  vector<string> nms;
  string nm;
  string key;
  nms = splitString(vec, ":");
  if (nms.size() > 1) {
    // TODO don't let users set namespace = "namespace"
    nm = nms[0];
    key = nms[1];
  } else {
    if (actionMap[nms[0]] == NAMESPACE) {
      nm = "";
      key = "";
    } else {
      nm = "default";
      key = nms[0];
    }
  }
  return make_tuple(nm,key);
}

bool MainRunner::check_if_namespace(string nm,string key) {
  return nm == "" && key == "";
}

string MainRunner::handle_line(string line){
  string msg;
  vector<string> keyvalue;
  kvAction action;
  string nm;
  string key;
  bool is_namespace;
  keyvalue = splitString(line);

  //for (auto s : keyvalue)
  //  cout << "'" << s << "' (" << s.size() << ") ";
  //cout << endl;
  action = actionMap[keyvalue[0]];
  switch(action) {
    case GET:
      tie(nm,key) = get_namespace_and_key(keyvalue[1]);
      // TODO refactor this - repetitive
      if (namespaces.count(nm) > 0) {
        msg = namespaces[nm].get_key(key);
      } else {
        msg = nm + " does not exist as a namespace";
      }
      break;
    case SET:
      tie(nm,key) = get_namespace_and_key(keyvalue[1]);
      is_namespace = check_if_namespace(nm,key);
      if (is_namespace) {
        msg = set_namespace(namespaces, keyvalue[2]);
      } else {
        msg = set_namespace(namespaces, nm);
        msg += namespaces[nm].set_key(key, keyvalue[2]);
      }
      break;
    case DELETE:
      tie(nm,key) = get_namespace_and_key(keyvalue[1]);
      is_namespace = check_if_namespace(nm,key);
      if (is_namespace) {
        msg = delete_namespace(namespaces, keyvalue[2]);
      } else {
        if (namespaces.count(nm) > 0) {
          msg = namespaces[nm].delete_key(key);
        } else {
          msg = nm + " does not exist as a namespace";
        }
      }
      break;
    case LIST:
      nm = keyvalue.size() > 1 ? keyvalue[1] : "default";
      if (namespaces.count(nm) > 0) {
        msg = namespaces[nm].list_keys();
      } else {
        msg = nm + " does not exist as a namespace";
      }
      break;
    default:
      msg = "please use one of the following actions\n'get', 'set', 'delete', 'list'";
      break;
  }
  msg = msg + "\n";
  return msg;
}
