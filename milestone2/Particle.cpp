#include "Particle.h"

#include "Debug.h"
#include "EventQueue.h"

#include <iostream>

Particle::Particle(const std::string &i, const Vector &loc, const Number &m)
 : id(i), kinematics(std::vector<Vector>(3)), mobility(1.0/m)
{
   kinematics[0] = loc;
}

void Particle::Update() {
   Number curTime = EventQueue::GetEventQueue()->GetTime();

   if (curTime != lastTime) {
      Number timeDelta = EventQueue::GetEventQueue()->GetTime() - lastTime;

      kinematics[LOC] = kinematics[LOC] + kinematics[VEL].Scale(timeDelta) +
       kinematics[ACC].Scale(timeDelta * timeDelta * 0.5);

      kinematics[VEL] = kinematics[VEL] + kinematics[ACC].Scale(timeDelta);

#ifdef DEBUG
      std::cout << std::fixed << std::setprecision(NumTraits::PRECISION) <<
       "Part " << id << " moves at (" << kinematics[VEL] << ") to (" <<
       kinematics[LOC] << ") at " << EventQueue::GetEventQueue()->GetTime() <<
       ")" << std::endl;
#endif

      lastTime = curTime;
   }
}
