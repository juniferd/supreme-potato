#include "kv.h"

string KeyValue::list_keys() {
  string msg;
  for (map<string,string>::iterator i = kv.begin(); i != kv.end(); ++i) {
    msg += i->first + " ";
  }
  return msg;
}
string KeyValue::get_key(string key) {
  string msg;

  if (kv.count(key)) {
    msg = "Get " + key + ": " + kv[key];
  } else {
    msg = key + " not found";
  }
  return msg;
}

string KeyValue::set_key(string key,string value) {
  string msg;

  // check if key already exists
  if (kv.count(key)) {
    msg = key + " already existed and has been overwritten with " + value;
  } else {
    msg = key + " set to " + value;
  }
  kv[key] = value;
  return msg;
}

string KeyValue::delete_key(string key) {
  string msg;
  int count = kv.erase(key);
  if (count) {
    msg = "Deleted key " + key;
  } else {
    msg = "Unable to delete key: " + key;
  }
  return msg;
}
