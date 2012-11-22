#include "ForceEvent.h"

#include "Force.h"

void ForceEvent::Execute()
{
   force->Update();
}
