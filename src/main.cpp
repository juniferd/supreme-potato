#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "runner.h"
using namespace std;

int main() {
  string line;
  MainRunner runner;

  while (getline (cin, line)) {
    cout << runner.handle_line(line);
  }

  return 0;
}
