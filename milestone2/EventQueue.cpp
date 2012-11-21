#include "EventQueue.h"

#include "Event.h"

// static
const Heap<TCmpPtr<Event> > &EventQueue::GetEventQueue()
{
   // TODO how to initiailize to NULL?
   if (events == NULL)
      events = new Heap<TCmpPtr<Event> >(INIT_SIZE);
   return *events;
}

// static
void EventQueue::AddEvent(Event *e)
{
   events->Add(TCmpPtr<Event>(e));
}

// static
Number EventQueue::GetTime()
{
   return lastTime;
}

// static
bool EventQueue::Advance()
{
   Event *event;
   long ret;

   ret = events->Remove((TCmpPtr<Event> *) &event);
   if (ret != -1) {
      lastTime = event->GetTime();
      event->Execute();
      return true;
   }

   return false;
}

// static
void EventQueue::Clear()
{
   Event *event;
   while (events->Remove((TCmpPtr<Event> *) &event) != -1)
      ;
}

EventQueue::EventQueue() { }

EventQueue::~EventQueue() { }
