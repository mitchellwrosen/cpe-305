#ifndef GRAVITYFORCE_H
#define GRAVITYFORCE_H

#include "Particle.h"
#include "Force.h"

// Force reflecting gravitational attraction between two Particles.  Uses
// a static Parameters value that specifies computational parameters for
// all GravityForce objects.
//
// Add member data, and perhaps initializers to the constructor, as needed.
// Don't add other methods.
class GravityForce : public Force {
public:
   // General computational Parameters:
   // G -- gravitational constant using the units of the simulation.
   // accuracy -- Schedule an update when the current velocities of the target
   //   particles will add a delta-vector to the current inter-particle vector
   //   such that the delta-vector has length accuracy*|current vector|.  So,
   //   if current interparticle vector has length 42, and accuracy is .01,
   //   schedule the next update when a vector-delta of length .42 is predicted.
   // minWait -- The above computation may result in very short wait, e.g. if
   //   the particles are very close.  Many short updates can slow the
   //   simulation, so wait at least minWait for the next Update. (This is 
   //   inaccurate, of course, and later versions may instead do closed-form
   //   two-body predictions for such "close pass" situations.)
   // maxWait -- The above computation may result in infinite wait, e.g. if
   //   neither target particle is currently moving.  Wait at most maxWait for
   //   the next Update.
   // minDist -- Assume interparticle distance is always at least minDist when
   //   computing update times and gravitational force.  Otherwise coincident
   //   particles would result in infinite gravity.
   struct Parameters {
      Number G;
      Number accuracy;
      Number minWait;
      Number maxWait;
      Number minDist;     
      
      Parameters(Number g, Number a, Number minW, Number maxW, Number mD)
       : G(g), accuracy(a),minWait(minW),  maxWait(maxW), minDist(mD) {}
   };
   
   GravityForce(Particle *pa, Particle *pb) : p1(pa), p2(pb) {}

   virtual Number Update();
   
   static void SetParameters(const Parameters &val) {prms = val;}

private:
};

#endif
