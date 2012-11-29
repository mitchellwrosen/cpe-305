#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>

using namespace std;
typedef map<string, set<int> > Map;

int main(int argc, const char **argv) {
   Map map;
   string line, sub;
   int lineNum = 0;

   while (lineNum++, getline(cin, line)) {
      istringstream iss(line);
      while (iss >> sub)
         map[sub].insert(lineNum);
   }

   for (Map::iterator iter = map.begin(); iter != map.end(); ++iter) {
      cout << iter->first << " appears on";
      for (set<int>::iterator iter2 = iter->second.begin();
            iter2 != iter->second.end(); iter2++)
         cout << " " << *iter2;
      cout << endl;
   }

   return 0;
}
