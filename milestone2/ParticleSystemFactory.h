#ifndef PARTICLESYSTEMFACTORY_H
#define PARTICLESYSTEMFACTORY_H

#include "Particle.h"
#include "Force.h"

// A ParticleSystemFactory (PSF) creates a system of particles and their
// related forces.  It returns each as appropriate vector sets. The
// PSF creates the Force and Particle objects, and (generally) owns them.
// See derived class comments for more details.

// Leave this base class unchanged!

class ParticleSystemFactory {
public:
   typedef std::vector<Particle *> PrtVector;
   typedef std::vector<Force *> FrcVector;
   
   virtual PrtVector GetParticles() = 0;
   virtual FrcVector GetForces() = 0;
};

#endif
