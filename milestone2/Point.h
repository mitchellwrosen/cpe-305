#ifndef POINT_H
#define POINT_H

#include "Particle.h"

// Point adds just a color to Particle, suitable for point-sprite display
class Point : public Particle {
public:
   Point(const std::string &i, const std::vector<Vector> &k, const Number &m,
    int c)
    : Particle(i, k, m), color(c) { }

   Point(const std::string &i, const Vector &loc, const Number &m, int c)
    : Particle(i, loc, m), color(c) { }

   virtual void Visit(ParticleVisitor *);

   const int &GetColor() const { return color; }

protected:
   int color;
};

#endif
