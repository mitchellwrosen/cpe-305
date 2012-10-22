#include <cstdlib>
#include "Dialog.h"

// static
void Dialog::ReadLimitInt(std::istream &is, std::ostream &os,
    int *val, int lo, int hi, std::string prompt)
{
   std::string line;
   const char *nptr;
   char *endptr;
   os << prompt;
   is >> line;
   nptr = line.c_str();

   *val = strtol(nptr, &endptr, 10);
   if (*endptr) {
      os << "Unexpected garbage after value.";
      *val = -1335;
   }
}
