#include "GravityForce.h"

#include "EventQueue.h"
#include "MyLib.h"
#include "NumTraits.h"

#include "Debug.h"

// static
GravityForce::Parameters GravityForce::prms = GravityForce::Parameters(0, 0, 0,
 0, 0);

Number GravityForce::Update()
{
   Number dist;
   Vector newAcc1, newAcc2;
   std::vector<Vector> p1k, p2k;

#ifdef DEBUG
   Number origDist = TMax<Number>((p1->GetKinematics()[Particle::LOC] -
    p2->GetKinematics()[Particle::LOC]).Length(), prms.minDist);
#endif

   p1->Update();
   p2->Update();

   p1k = p1->GetKinematics();
   p2k = p2->GetKinematics();

   dist = TMax<Number>((p1k[Particle::LOC] - p2k[Particle::LOC]).Length(),
    prms.minDist);

   newAcc1 = (p2k[Particle::LOC] - p1k[Particle::LOC]).Unit().Scale(
    prms.G * (1.0 / p2->GetMobility()) / (dist * dist));
   newAcc2 = (p1k[Particle::LOC] - p2k[Particle::LOC]).Unit().Scale(
    prms.G * (1.0 / p1->GetMobility()) / (dist * dist));

   // p2 on p1
   p1k[Particle::ACC] = p1k[Particle::ACC] + newAcc1 - lastAcc1;
#ifdef DEBUG
   std::cout << "Update force between " << p1->GetId() << " and " << p2->GetId()
    << ". (" << p1->GetKinematics()[Particle::ACC] << ")->(" <<
    p1k[Particle::ACC] << ")" << std::endl << std::endl;
#endif
   p1->SetKinematics(p1k);

   // p1 on p2
   p2k[Particle::ACC] = p2k[Particle::ACC] + newAcc2 - lastAcc2;
   p2->SetKinematics(p2k);

   // Update lastAcc1 and lastAcc2.
   lastAcc1 = newAcc1;
   lastAcc2 = newAcc2;

   //
   //          |(P1.Loc - P2.Loc)|^2 * accuracy
   // T = Sqrt(--------------------------------)
   //               |(P1.Vel - P2.Vel)|^2
   //
   // T = Bound(min, T, max)
   //
   Number wait = Bound<Number>(prms.minWait, NumTraits::Sqrt((
    p1k[Particle::LOC] - p2k[Particle::LOC]).LengthSqr() * prms.accuracy /
    (p1k[Particle::VEL] - p2k[Particle::VEL]).LengthSqr()), prms.maxWait);
#ifdef DEBUG
   std::cout << std::fixed << std::setprecision(6) <<
    "Deltaspeed " << (p1k[Particle::VEL]-p2k[Particle::VEL]).Length() <<
    " dist " << dist << " wait: " << wait << std::endl;
#endif
   return EventQueue::GetEventQueue()->GetTime() + wait;
}
