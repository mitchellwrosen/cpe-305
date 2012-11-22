#include "GravityPSF.h"

#include "GravityForce.h"

void GravityPSF::AddChild(ParticleSystemFactory *psf)
{
   PrtVector childParticles(psf->GetParticles());
   FrcVector childForces(psf->GetForces());

   // Add a new GravityForce for each in |particles| to |psf->particles|.
   for (std::vector<Particle *>::iterator iter1 = particles.begin();
        iter1 != particles.end(); ++iter1) {
       for (std::vector<Particle *>::iterator iter2 = childParticles.begin();
            iter2 != childParticles.end(); ++iter2) {
          forces.push_back(new GravityForce(*iter1, *iter2));
       }
   }

   // Append child particles and forces.
   for (std::vector<Particle *>::iterator iter = childParticles.begin();
        iter != childParticles.end(); ++iter) {
      particles.push_back(*iter);
   }

   for (std::vector<Force *>::iterator iter = childForces.begin();
        iter != childForces.end(); ++iter) {
      forces.push_back(*iter);
   }
}
