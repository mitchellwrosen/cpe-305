#ifndef GLOBULARCLUSTERPSF_H
#define GLOBULARCLUSTERPSF_H

#include "ParticleSystemFactory.h"
#include "NumTraits.h"

using NumTraits::Number;

// A PSF that produces a set of Point particles, and their associated
// GravityForces, modelling a galactic globular cluster.  In particular,
// this PSF creates Points in a 3-D grid pattern centered on a "center"
// location. The central Point is at "center", with Points around it
// at distances of "interval".  All Points within "radius" of "center"
// are included.   Point masses vary from "loMass" for the center Point,
// with masses increasing linearly by distance from "center", up to hiMass
// for Points exactly "radius" from "center".
//
// Do not change this header at all.  You may find it useful to know, for
// matching my output, that the order of Points is by X dimension, then
// by Y for identical X's, and then by Z.
class GlobularClusterPSF : public ParticleSystemFactory {
public:
   GlobularClusterPSF(const std::string &n, const Vector& center, Number radius,
    Number interval, Number loMass, Number hiMass);
   PrtVector GetParticles() {return particles;}
   FrcVector GetForces()    {return forces;}
   
private:
   PrtVector particles;
   FrcVector forces;
};

#endif
