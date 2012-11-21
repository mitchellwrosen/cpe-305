#include "Particle.h"

#include "EventQueue.h"

void Particle::Update() {
   Number timeDelta = EventQueue::GetTime() - lastTime;

   kinematics[LOC] = kinematics[LOC] + kinematics[VEL].Scale(timeDelta) +
    kinematics[ACC].Scale(timeDelta * timeDelta * 0.5);

   kinematics[VEL] = kinematics[VEL] + kinematics[ACC].Scale(timeDelta);
}
