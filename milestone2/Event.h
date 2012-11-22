#ifndef EVENT_H
#define EVENT_H

#include "NumTraits.h"

using NumTraits::Number;

// Base class for all Events posted to the EventQueue.  Events
// share common properties of time and the ability to be "Executed"
// the meaning of which varies per Event subclass. 
//
// Leave this base class unchanged except for adding one method.

class Event {
public:
   Event(Number t) : time(t) {}
   
   Number GetTime() {return time;}
   virtual void Execute() = 0;

protected:
   Number time;
};

#endif
