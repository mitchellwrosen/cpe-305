#ifndef GRAVITYPSF_H
#define GRAVITYPSF_H

#include <vector>
#include "NumTraits.h"
#include "ParticleSystemFactory.h"

// GravityPSF is a composite PSF, which takes ownership of Particles and Forces
// from its child PSFs, and also adds GravityForces between all Particle pairs
// between particles from different child PSFs.  (So, if you add two child PSFs,
// one with 10 Particles and Forces, and the other with 20, then GravityPSF will
// aggregate all the Particles and Forces from the child PSFs, and will also add
// 200 GravityForces between Particles from the two child PSFs.  GravityPSF starts
// with no children.
//
// Do not modify this header.
class GravityPSF : public ParticleSystemFactory {
public:
   GravityPSF() {}
   PrtVector GetParticles() {return particles;}
   FrcVector GetForces()    {return forces;}

   void AddChild(ParticleSystemFactory *psf);

private:
   PrtVector particles;
   FrcVector forces;
};

#endif
