#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
namespace kv {
  string getKey(map<string,string> &kv, string key);
  string setKey(map<string,string> &kv,string key,string value);
  string deleteKey(map<string,string> &kv,string key);
  string listKeys(map<string,string> &kv);
}
