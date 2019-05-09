#include <map>
#include <string>
using namespace std;
enum kvAction {GET, SET, DELETE, LIST};
map<string, kvAction> actionMap = {{"get",GET},{"set",SET},{"delete",DELETE},{"list",LIST}};
