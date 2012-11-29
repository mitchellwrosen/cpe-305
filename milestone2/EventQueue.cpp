#include "EventQueue.h"

#include "Event.h"

// static
long EventQueue::INIT_SIZE = 1000;

// static
EventQueue *EventQueue::eventQueue = NULL;

// static
EventQueue *EventQueue::GetEventQueue(int size)
{
   if (eventQueue == NULL)
      eventQueue = new EventQueue(size);
   return eventQueue;
}

EventQueue::EventQueue(int size)
{
   lastTime = 0;
   events = new EventHeap(size);
}

void EventQueue::AddEvent(Event *e)
{
   events->Add(TCmpPtr<Event>(e));
}

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

   Clear();
   return false;
}

void EventQueue::Clear()
{
   Event *event;
   while (events->Remove((TCmpPtr<Event> *) &event) != -1)
      ;
}
