#include "ForceEvent.h"

#include "EventQueue.h"
#include "Force.h"

void ForceEvent::Execute()
{
   Number nextTime = force->Update();
   EventQueue::GetEventQueue()->AddEvent(new ForceEvent(nextTime, force));
}
