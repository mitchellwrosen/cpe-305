#ifndef NUMTRAITS_H
#define NUMTRAITS_H

#include <cmath>

namespace NumTraits {
   typedef double Number;

   const int PRECISION = 3;
   const Number ROUND_FACTOR = pow(10.0, PRECISION);

   inline double Round(double val) {
      return (int)(val * ROUND_FACTOR + .5) / ROUND_FACTOR;
   }

   inline double Sin(double n) { return sin(n); }
   inline double Cos(double n) { return cos(n); }
   inline double Sqrt(double n) { return sqrt(n); }
};

#endif
