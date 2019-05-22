#ifndef RUNNER_H
#define RUNNER_H
#include <string>
#include <map>
#include <tuple>
#include "kv.h"
using namespace std;
class MainRunner {
private:
  map<string,KeyValue> namespaces;
  string set_namespace(map<string,KeyValue> &namespaces, string nm);
  string delete_namespace(map<string,KeyValue> &namespaces, string nm);
  tuple<string,string> get_namespace_and_key(string vec);
  bool check_if_namespace(string nm, string key);
public:
  string handle_line(string line);
};
#endif
