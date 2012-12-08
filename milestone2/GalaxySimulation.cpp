#include "EventQueue.h"
#include "GlobularClusterPSF.h"
#include "GravityPSF.h"
#include "GravityForce.h"
#include "Point.h"
#include "ForceEvent.h"
#include "FrameEvent.h"

#include <iostream>
#include <iomanip>

static const Number LOMASS = 1;  // Fixed mass range for all GlobularClusterPSFs
static const Number HIMASS = 5;
static const Number minDist = .01; // MinDist for GravityForces
static const Number G = 1.5e-13; // G in units of years, lightyears, and solar masses

using namespace std;

// Generates XML output describing Particles
class PropertyVisitor : public ParticleVisitor {
   virtual void VisitSphere(Sphere *sphere) { }

   virtual void VisitPoint(Point *point)
   {
      cout << "<Point id=\"" << point->GetId() << "\" color=\"" << hex <<
       uppercase << point->GetColor() << dec << nouppercase << "\"/>" << endl;
   }
};

int main() {
   int numFrames;
   string name;
   Number x, y, z, radius, interval, accuracy, maxWait, minWait, frameTime;
   vector<Particle *> particles;
   vector<Force *> forces;
   // Several declarations need adding here.
   GravityPSF *psf;
   PropertyVisitor propertyVisitor;
   EventQueue *eventQueue;


   cin >> frameTime >> numFrames >> accuracy >> minWait >> maxWait;
   // Two lines needed here.
   GravityForce::Parameters prms(G, accuracy, minWait, maxWait, minDist);
   GravityForce::SetParameters(prms);

   // Read a name, x/y/z location, radius and interval for a GlobularClusterPSF, until
   // EOF.  Create each globular cluster, and merge them using a GravityPSF.
   psf = new GravityPSF();
   while (cin >> name >> x >> y >> z >> radius >> interval) {
      GlobularClusterPSF *child = new GlobularClusterPSF(name, Vector(x, y, z),
       radius, interval, LOMASS, HIMASS);
      psf->AddChild(child);
   }

   // Start the Movie output, and traverse all Particles to produce initial property output.
   // Use a ParticleVisitor for this.
   cout << "<Movie frameRate=\"24\">" << endl << "<Objects>" << endl;
   particles = psf->GetParticles();
   for (vector<Particle *>::iterator itr = particles.begin();
    itr != particles.end(); itr++) {
      (*itr)->Visit(&propertyVisitor);
   }
   cout << "</Objects>" << endl;

   // Create and schedule an initial ForceEvent for all Forces, and schedule one FrameEvent.
   eventQueue = EventQueue::GetEventQueue();
   forces = psf->GetForces();
   for (vector<Force *>::iterator itr = forces.begin(); itr != forces.end();
    itr++) {
      eventQueue->AddEvent(new ForceEvent(0, *itr));
   }
   eventQueue->AddEvent(new FrameEvent(particles, frameTime, numFrames));

#ifdef DEBUG
   cout << "Starting simulation with " << particles.size() <<
    " particles and " << forces.size() << " forces" << endl;
#endif

   // Advance the simulation till done, and add closing tag.
   while (eventQueue->Advance())
      ;
   cout << "</Movie>";

   delete psf;
}
