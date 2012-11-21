#ifndef FORCE_H
#define FORCE_H

#include "NumTraits.h"

using NumTraits::Number;

// Force characterizes a general force, which may apply to one
// or more Particles, depending on the nature of the force. The
// general force design presumes that each force object will retain
// state indicating when it was last applied, and will update the
// affected Particles to the current time, and then adjust their
// acceleration to reflect the current value of the force.

// Do not change this base class!

class Force {
public:
   // Update target Particles' kinematics to take account of the
   // effect of the Force till the current clock time.  Return the
   // time at which the next Apply call should be scheduled.
   virtual Number Update() = 0;
};

#endif
