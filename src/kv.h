#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
class KeyValue {
private:
  map<string,string> kv;
public:
  string get_key(string key);
  string set_key(string key,string value);
  string delete_key(string key);
  string list_keys();
};
