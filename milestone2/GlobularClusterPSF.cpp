#include "GlobularClusterPSF.h"

#include "GravityForce.h"
#include "Point.h"

#include <sstream>

namespace {
   std::string PointToString(const std::string &n, int x, int y, int z)
   {
      std::stringstream ss;
      ss << n << "[" << x << "," << y << "," << z << "]";
      return ss.str();
   }

   //std::string PointToString(const std::string &n, const Vector &loc)
   //{
      //std::stringstream ss;
      //ss << n << "[" << loc.GetX() << "," << loc.GetY() << "," << loc.GetZ() <<
       //"]";
      //return ss.str();
   //}
}

GlobularClusterPSF::GlobularClusterPSF(const std::string &n,
 const Vector& center, Number radius, Number interval, Number loMass,
 Number hiMass)
{
   Point *point;
   Vector loc;
   Number dist;

   int numIntervals = radius / interval;

   //for (Number x = center.GetX() - interval * numIntervals;
    //x <= center.GetX() + interval * numIntervals; x += interval) {
      //for (Number y = center.GetY() - interval * numIntervals;
       //y <= center.GetY() + interval * numIntervals; y += interval) {
         //for (Number z = center.GetZ() - interval * numIntervals;
          //z <= center.GetZ() + interval * numIntervals; z += interval) {
            //loc = Vector(x, y, z);
            //dist = (center - loc).Length();

            //if (dist <= radius) {
               //point = new Point(PointToString(n, loc - center), loc,
                //loMass + (dist / radius) * (hiMass - loMass),
                //0x0F0F0F + (dist / radius) * 0xF0F0F0);

               //particles.push_back(point);
            //}
         //}
      //}
   //}

   for (int x = -numIntervals; x <= numIntervals; x++) {
      for (int y = -numIntervals; y <= numIntervals; y++) {
         for (int z = -numIntervals; z <= numIntervals; z++) {
            loc = Vector(
             center.GetX() + x * interval,
             center.GetY() + y * interval,
             center.GetZ() + z * interval);
            dist = (center - loc).Length();

            if (dist <= radius) {
               point = new Point(PointToString(n, x, y, z), loc,
                loMass + (dist / radius) * (hiMass - loMass),
                0x0F0F0F + (dist / radius) * 0xF0F0F0);

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
