#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

string getKey(
    map<string,string> &kv,
    string key
    ) {
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

string setKey(
    map<string,string> &kv,
    string key,
    string value
    ) {
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

string deleteKey(
    map<string,string> &kv,
    string key
    ) {
  string msg;
  int count = kv.erase(key);
  if (count) {
    msg = "Deleted key " + key;
  } else {
    msg = "Unable to delete key: " + key;
  }
  return msg;
}

vector<string> splitString (string sentence, string delimiter) {
  string word;
  int start = 0;
  int senLen = sentence.length();
  vector<string> words;

  for (int i = 0; i < senLen; i++) {
    char c = sentence[i];
    if (delimiter.find(c) != std::string::npos) {
      words.push_back(sentence.substr(start, i - start));
      start = i+1;
    } else if (i == senLen - 1) {
      words.push_back(sentence.substr(start, senLen - start));
    }
  }

  return words;
}

vector<string> splitString (string sentence) {
  return splitString(sentence, " ");
}

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
