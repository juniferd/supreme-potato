#include <string>
#include <map>
#include "kv.h"
using namespace std;
class MainRunner {
private:
  map<string,KeyValue> namespaces;
  void check_kv_in_namespace(map<string, KeyValue> &namespaces, string nm);
  vector<string> get_namespace_and_key(string vec);
public:
  string handle_line(string line);
};
