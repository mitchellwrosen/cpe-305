#include "GravityForce.h"

Number GravityForce::Update()
{
   // p1 on p2
   p1->GetKinematics()[Particle::ACC];
   std::vector<Vector> newKinematics = p1->GetKinematics();
   newKinematics[Particle::ACC] = p1->GetMobility() *  


   acc = 1/m * f = G * m1 * m2 / r^2
}
