#ifndef NUMTRAITS_H
#define NUMTRAITS_H

#include <cmath>

namespace NumTraits {
   typedef double Number;

   const int PRECISION = 9;
   inline double Sin(double n) { return sin(n); }
   inline double Cos(double n) { return cos(n); }
   inline double Sqrt(double n) { return sqrt(n); }
};

#endif
