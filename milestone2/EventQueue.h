#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "NumTraits.h"
#include "MyLib.h"
#include "Heap.h"

using NumTraits::Number;

class Event;
template <class C> class Heap;

static long INIT_SIZE = 1000;

// Event queue for simulation.  Uses a Heap to maintain a priority
// queue of Event-derived objects, which objects are owned by *themselves*,
// not by the EventQueue.  Initial size of the heap is INIT_SIZE, or
// whatever is passed to the first call of GetEventQueue.
//
// EventQueue is also a singleton, and general "clock" for the simulation.
// The time of the most-recent event may be obtained at any time from the
// EventQueue.
//
// Method details:
// GetEventQueue(int size) -- Return singleton EventQueue, creating it with the
// specified initial size if needed.
//
// AddEvent(Event *e) -- Add event e to the queue, ordered by its time.
//
// GetTime() -- Return time of most recently dequeued Event.
//
// Advance() -- Remove next Event from the queue, and Execute it, if there
// are any Events.  Return true iff there was an Event to Execute.
//
// Clear() -- Eliminate all Events from the queue.  (Used in general to end
// the simulation when needed.
//
// Constructor and destructor are private.

class EventQueue {
// Fill in methods and member data reflecting the above comments.
public:
   static const Heap<TCmpPtr<Event> > &GetEventQueue(int size);
   static void AddEvent(Event *e);
   static Number GetTime();
   static bool Advance();
   static void Clear();

private:
   EventQueue();
   ~EventQueue();

   static Heap<TCmpPtr<Event> > *events;
   static Number lastTime;
};

#endif
