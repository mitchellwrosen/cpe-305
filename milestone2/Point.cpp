#include "Point.h"

#include <iostream>
#include <sstream>

void Point::Visit(ParticleVisitor *visitor)
{
   visitor->VisitPoint(this);
}
