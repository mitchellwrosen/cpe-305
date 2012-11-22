#ifndef FRAMEEVENT_H
#define FRAMEEVENT_H

#include <vector>
#include "ParticleVisitor.h"
#include "Event.h"

class Particle;

// Represents one frame-generation event.  The simulation uses
// just one such event, scheduled at time 0, and then rescheduling
// itself as needed.
//
// Do not change this header.
class FrameEvent : public Event {
public:
   class FrameVisitor : public ParticleVisitor {
      void VisitSphere(Sphere *) {}
      void VisitPoint(Point *p);
   };
   
   // Create a FrameEvent that generates an XML Frame output for
   // all Particles in "p", and which reschedules itself each "i"
   // time units, repeating "r" times, and then ending the simulation
   // after the "r"th Frame generation.
   FrameEvent( std::vector<Particle *> p, Number i, int r)
    : Event(0), prts(p), interval(i), reps(r) {}
   
   virtual void Execute();

protected:
   std::vector<Particle *> prts;
   Number interval;
   int reps;
};

#endif
