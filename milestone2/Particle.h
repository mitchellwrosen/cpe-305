#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include "Vector.h"
#include "ParticleVisitor.h"

// A Particle describes the essential properties of a physical
// object in the engine: an identifying string, the kinematics
// (location, velocity, and acceleration), and inverse mass
// ("mobility").  Additional properties, such as orientation and
// rotation, may be added by subclasses.
//
// The Particle also provides methods to support a Visitor based process
// of reporting or outputting information regarding it, via Visit.
//
// Finally, Particle tracks the last time at which it was updated, and its
// kinematics may be adjusted to the current time via a call of Update.
//
// Leave this base class unchanged!
class Particle {
public:
   Particle(const std::string &i, const std::vector<Vector> &k, const Number &m)
    : id(i), kinematics(k), mobility(1.0/m) { }

   Particle(const std::string &i, const Vector &loc, const Number &m);

   virtual void Visit(ParticleVisitor *) = 0;

   void Update();

   const std::string &GetId()                            {return id;}
   const std::vector<Vector> &GetKinematics()            {return kinematics;}
   void SetKinematics(const std::vector<Vector> &newVal) {kinematics = newVal;}
   Number GetMobility()                                  {return mobility;}
   Number GetLastTime()                                  {return lastTime;}

   enum {LOC, VEL, ACC};

protected:
   std::string id;
   std::vector<Vector> kinematics;
   Number mobility;
   Number lastTime;
};

#endif
