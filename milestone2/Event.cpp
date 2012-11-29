#include "Event.h"

bool Event::operator<(const Event& rhs) const
{
   return time > rhs.time;
}
