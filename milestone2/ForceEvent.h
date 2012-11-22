#ifndef FORCEEVENT_H
#define FORCEEVENT_H

#include "Event.h"

class Force;

// Event for updating a force. 
//
// Do not change this header file.

class ForceEvent : public Event {
public:
   ForceEvent(Number time, Force *f) : Event(time), force(f) {}
   
   void Execute();
   
private:
   Force *force;
};

#endif
