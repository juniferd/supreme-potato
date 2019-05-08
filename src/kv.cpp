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
  map<string,string>::iterator it;

  it = kv.find(key);
  if (it != kv.end()) {
    msg = key + ": " + kv[key];
  } else {
    msg = key + " not found";
  }
  return msg;
}

string KeyValue::set_key(string key,string value) {
  string msg;
  int count = kv.count(key);

  kv[key] = value;

  // check if key already exists
  if (count) {
    msg = key + " already existed and has been overwritten with " + value;
  } else {
    msg = "Key-value updated";
  }
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
