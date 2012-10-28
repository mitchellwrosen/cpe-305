#include <cstdlib>
#include "Dialog.h"
#include "MyLib.h"

// static
void Dialog::ReadLimitInt(std::istream &is, std::ostream &os,
    int *val, int lo, int hi, std::string prompt)
{
   int ret;
   char extra;
   std::string line;
   while (1) {
      os << prompt;
      getline(is, line);
      ret = sscanf(line.c_str(), "%d %c", val, &extra);
      if (ret == 0) {
         os << "Badly formatted input" << std::endl;
         continue;
      } else if (ret == 2) {
         os << "Unexpected garbage after value." << std::endl;
         continue;
      }

      if (InRange<int>(lo, *val, hi))
         break;

      os << "Please enter a value between " << lo << " and " << hi - 1 <<
       std::endl;
   }

}
