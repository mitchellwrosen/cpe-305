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
      printf("Part %s moves at (%0.4g, %0.4g, %0.4g) to "
       "(%0.4g, %0.4g, %0.4g) at %0.4g\n",
       id.c_str(),
       kinematics[VEL].GetX(),
       kinematics[VEL].GetY(),
       kinematics[VEL].GetZ(),
       kinematics[LOC].GetX(),
       kinematics[LOC].GetY(),
       kinematics[LOC].GetZ(),
       EventQueue::GetEventQueue()->GetTime());
#endif

      lastTime = curTime;
   }
}
