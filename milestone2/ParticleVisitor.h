#ifndef PARTICLEVISITOR_H
#define PARTICLEVISITOR_H

class Sphere;
class Point;

// General interface for visitors of Particles, including printing
// of Particle properties and updates.
class ParticleVisitor {
public:
   virtual void VisitSphere(Sphere *) {}
   virtual void VisitPoint(Point *)  {}
};

#endif
