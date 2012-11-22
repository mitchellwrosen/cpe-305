#include "EventQueue.h"
#include "GlobularClusterPSF.h"
#include "GravityPSF.h"
#include "GravityForce.h"
#include "Point.h"
#include "ForceEvent.h"
#include "FrameEvent.h"

static const Number LOMASS = 1;  // Fixed mass range for all GlobularClusterPSFs
static const Number HIMASS = 5;
static const Number minDist = 2; // MinDist for GravityForces
static const Number G = 1.5e-13; // G in units of years, lightyears, and solar masses

using namespace std;

// Fill in this main function as described in the comments.  Make no other changes or additions.

// Generates XML output describing Particles
class PropertyVisitor : public ParticleVisitor {
   // Fill in.
};

int main() {
   Number frameTime;
   int numFrames;
   string name;
   Number x, y, z, radius, interval, accuracy, maxWait, minWait;
   ParticleSystemFactory *child;
   vector<Particle *> particles;
   vector<Force *> forces;
   // Several declarations need adding here.

   cin >> frameTime >> numFrames >> accuracy >> minWait >> maxWait;
   // Two lines needed here.

   // Read a name, x/y/z location, radius and interval for a GlobularClusterPSF, until
   // EOF.  Create each globular cluster, and merge them using a GravityPSF.
   while (cin >> name >> x >> y >> z >> radius >> interval) {
      child = new GlobularClusterPSF(name, Vector(x, y, z), radius, interval,
       LOMASS, HIMASS);
      // Add a line or two....
   }

   // Start the Movie output, and traverse all Particles to produce initial property output.
   // Use a ParticleVisitor for this.
   printf("<Movie>\n<Objects>\n");
   particles = psf->GetParticles();
   for (vector<Particle *>::iterator itr = particles.begin(); itr != particles.end(); itr++)
      // Add one line.
   printf("</Objects>\n");

   // Create and schedule an initial ForceEvent for all Forces, and schedule one FrameEvent.
   forces = psf->GetForces();
   for (vector<Force *>::iterator itr = forces.begin(); itr != forces.end(); itr++)
      // Add one line
   // And one more after the loop.

   // Advance the simulation till done, and add closing tag.
   while (q->Advance())
      ;
   printf("</Movie>");

   delete psf;
}
