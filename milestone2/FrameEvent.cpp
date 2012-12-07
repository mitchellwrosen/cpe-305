#include "FrameEvent.h"

#include "EventQueue.h"
#include "Particle.h"
#include "Point.h"
#include "Vector.h"

void FrameEvent::FrameVisitor::VisitPoint(Point *point)
{
   Vector loc = point->GetKinematics()[Particle::LOC];
   std::cout.precision(3);
   std::cout.setf(std::ios::fixed, std::ios::floatfield);
   std::cout << "<Update id=\"" << point->GetId() << "\" position=\"" <<
    NumTraits::Round(loc.GetX()) << ", " << NumTraits::Round(loc.GetY()) <<
    ", " << NumTraits::Round(loc.GetZ()) << "\"/>" << std::endl;
}

void FrameEvent::Execute()
{
   FrameVisitor frameVisitor;
   FrameEvent *nextFrame;

   std::cout.precision(3);
   std::cout.setf(std::ios::fixed, std::ios::floatfield);
   std::cout << "<Frame time=\"" << time << "\">" << std::endl;
   for (std::vector<Particle *>::iterator iter = prts.begin();
        iter != prts.end(); ++iter) {
      (*iter)->Update();
      (*iter)->Visit(&frameVisitor);
   }
   std::cout << "</Frame>" << std::endl;

   if (--reps > 0) {
      nextFrame = new FrameEvent(prts, interval, reps);
      nextFrame->time = time + interval;

      EventQueue::GetEventQueue()->AddEvent(nextFrame);
   } else {
      EventQueue::GetEventQueue()->Clear();
   }
}
