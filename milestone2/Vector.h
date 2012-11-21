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
   Number Dot(const Vector &other) const {
      return x*other.x + y*other.y + z*other.z;
   }

   // Vector sum
   Vector operator+(const Vector &other) const {
      return Vector(x+other.x, y+other.y, z+other.z);
   }

   // Vector difference
   Vector operator-(const Vector &other) const {
      return Vector(x-other.x, y-other.y, z-other.z);
   }

   // Vector cross product
   Vector Cross(const Vector &other) const {
      return Vector(y*other.z - z*other.y, z*other.x - x*other.z,
       x*other.y - y*other.x);
   }

   // Multiply this Vector by factor, and return result.
   Vector Scale(Number factor) const {
      return Vector(x*factor, y*factor, z*factor);
   }

   // Return squared length of this Vector
   Number LengthSqr() const {
      return x*x + y*y + z*z;
   }

   // Return length of this Vector
   Number Length() const {
      return NumTraits::Sqrt(x*x + y*y + z*z);
   }

   // Return Vector that is the unit-length version of this Vector
   // Assumes this Vector is nonzero.
   Vector Unit() const {
      return Vector(x/Length(), y/Length(), z/Length());
   }

   Number GetX() const   { return x; }
   Number GetY() const   { return y; }
   Number GetZ() const   { return z; }
   void SetX(Number val) { x = val;  }
   void SetY(Number val) { y = val;  }
   void SetZ(Number val) { z = val;  }

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
