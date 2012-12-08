#include "GravityForce.h"

#include "EventQueue.h"
#include "MyLib.h"
#include "NumTraits.h"

// static
GravityForce::Parameters GravityForce::prms = GravityForce::Parameters(0, 0, 0,
 0, 0);

Number GravityForce::Update()
{
   Number dist;
   Vector deltaAcc1, deltaAcc2, force;
   std::vector<Vector> p1k, p2k;

   p1->Update();
   p2->Update();

   p1k = p1->GetKinematics();
   p2k = p2->GetKinematics();

   dist = TMax<Number>((p1k[Particle::LOC] - p2k[Particle::LOC]).Length(),
    prms.minDist);

   force = (p2k[Particle::LOC] - p1k[Particle::LOC]).Unit().Scale(
    (1.0 / p1->GetMobility()) * (1.0 / p2->GetMobility()) * prms.G /
    (dist * dist));

   p1k[Particle::ACC] = p1k[Particle::ACC] + (force - oldForce).Scale(
    p1->GetMobility());

   p2k[Particle::ACC] = p2k[Particle::ACC] + (oldForce - force).Scale(
    p2->GetMobility());

#ifdef DEBUG
   printf("Update force between %s and %s. (%0.4g, %0.4g, %0.4g)->"
    "(%0.4g, %0.4g, %0.4g)\n\n",
    p1->GetId().c_str(), p2->GetId().c_str(),
    oldForce.GetX(),
    oldForce.GetY(),
    oldForce.GetZ(),
    force.GetX(),
    force.GetY(),
    force.GetZ());
#endif

   p1->SetKinematics(p1k);
   p2->SetKinematics(p2k);

   oldForce = force;

   //
   //          |(P1.Loc - P2.Loc)|^2 * accuracy
   // T = Sqrt(--------------------------------)
   //               |(P1.Vel - P2.Vel)|^2
   //
   // distance * Sqrt(accuracy)
   // -------------------------
   //      |vel1 - vel2|
   //
   // T = Bound(min, T, max)
   //
   Number wait = Bound<Number>(prms.minWait,

         NumTraits::Sqrt(dist * dist * prms.accuracy / (p1k[Particle::VEL] - p2k[Particle::VEL]).LengthSqr()),
         //dist * NumTraits::Sqrt(prms.accuracy) / (p1k[Particle::VEL] - p2k[Particle::VEL]).Length(),

   prms.maxWait);

#ifdef DEBUG
   printf("Deltaspeed %0.4g dist %0.4g wait: %0.4g\n",
    (p1k[Particle::VEL]-p2k[Particle::VEL]).Length(), dist, wait);
#endif

   return EventQueue::GetEventQueue()->GetTime() + wait;
}
