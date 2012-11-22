#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iomanip>

#include "NumTraits.h"

using NumTraits::Number;

class Quaternion;
class Matrix;

// Vector represents a 3-D quantity (e.g. location, velocity, acceleration)
// including various methods for adding, subtracting, etc. such entities.
// It consistently uses NumTraits::Number so that it may be readily adjusted
// to use any numerical representation.
//
// Fill in the missing methods of Vector

class Vector {
public:
   friend class Quaternion;
   friend class Matrix;

   Vector(const Number &xp = 0, const Number &yp = 0, const Number &zp = 0) :
    x(xp), y(yp), z(zp) {}

   // Dot-product of this Vector and another

   // Vector sum
   Vector operator+...

   // Vector difference
   Vector operator-...

   // Vector cross product
   Vector Cross....

   // Multiply this Vector by factor, and return result.
   Vector Scale...

   // Return squared length of this Vector
   Number LengthSqr()...

   // Return length of this Vector
   Number Length()...

   // Return Vector that is the unit-length version of this Vector
   // Assumes this Vector is nonzero.
   Vector Unit()...
   
   Number GetX() const     {return x;}
   Number SetX(Number val) {x = val;}
   Number GetY() const     {return y;}
   Number SetY(Number val) {y = val;}
   Number GetZ() const     {return z;}
   Number SetZ(Number val) {z = val;}

   friend std::istream &operator>>(std::istream &is, Vector &v) {
      return is >> v.x >> v.y >> v.z;
   }

   friend std::ostream &operator<<(std::ostream &os, const Vector &v) {
      return os << std::fixed << std::setprecision(NumTraits::PRECISION)
       << v.x << ", " << v.y << ", " << v.z;
   }

private:
   Number x;
   Number y;
   Number z;
};

#endif
