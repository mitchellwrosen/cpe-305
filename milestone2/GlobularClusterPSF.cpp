#include "GlobularClusterPSF.h"

#include "GravityForce.h"
#include "Point.h"

#include <sstream>

GlobularClusterPSF::GlobularClusterPSF(const std::string &n,
 const Vector& center, Number radius, Number interval, Number loMass,
 Number hiMass)
{
   Point *point;
   Vector loc;
   Number dist;

   int numIntervals = radius / interval;

   for (int x = -numIntervals; x <= numIntervals; x++) {
      for (int y = -numIntervals; y <= numIntervals; y++) {
         for (int z = -numIntervals; z <= numIntervals; z++) {
            loc = Vector(x, y, z).Scale(interval);
            dist = loc.Length();

            if (dist <= radius) {
               std::stringstream ss;
               ss << n << "[" << x << "," << y << "," << z << "]";

               point = new Point(ss.str(), loc + center,
                loMass + (dist / radius) * (hiMass - loMass),
                (int) (0x0F0F0F + dist * 0xF0F0F0 / radius));

               particles.push_back(point);
            }
         }
      }
   }

   // Add a GravityForce from every existing Point to this one.
   for (PrtVector::iterator iter1 = particles.begin();
        iter1 != particles.end(); ++iter1) {
      for (PrtVector::iterator iter2 = iter1 + 1;
           iter2 != particles.end(); ++iter2) {
         forces.push_back(new GravityForce(*iter1, *iter2));
      }
   }
}
