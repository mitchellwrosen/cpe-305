#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>

using namespace std;
typedef map<string, set<int> > Map;

int main() {
   Map map;
   string line, sub;
   int lineNum = 0;
   while (lineNum++, getline(cin, line)) {
      istringstream iss(line);
      while (iss >> sub)
         map[sub].insert(lineNum);
   }
   for (Map::iterator i = map.begin(); i != map.end(); ++i) {
      cout << left << setw(20) << i->first << " appears on";
      for (set<int>::iterator j = i->second.begin(); j != i->second.end(); j++)
         cout << " " << *j;
      cout << endl;
   }
}
