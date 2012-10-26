#include <cstdlib>
#include "Dialog.h"
#include "MyLib.h"

// static
void Dialog::ReadLimitInt(std::istream &is, std::ostream &os,
    int *val, int lo, int hi, std::string prompt)
{
   std::string line;
   while (1) {
      os << prompt;
      is >> *val;

      if (is.fail()) {
         os << "Badly formatted input" << std::endl;
         is >> line;
         is.clear();
         continue;
      }

      if (!is.eof()) {
         os << "Unexpected garbage after value." << std::endl;
         continue;
      }

      if (InRange<int>(lo, *val, hi))
         break;
      os << "Please enter a value between " << lo << " and " << hi - 1 <<
       std::endl;
   }

}
