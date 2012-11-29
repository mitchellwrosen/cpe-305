# General test makefile for multi-target test
# Copyright Clinton Staley 12/1/01


# General definitions
CPP = g++
PROFFLAGS =
CPPFLAGS = $(PROFFLAGS) -Wall -std=c++98 -g

SIMOBJS = Event.o EventQueue.o ForceEvent.o FrameEvent.o GlobularClusterPSF.o \
          GravityForce.o GravityPSF.o Particle.o Point.o
OBJS = GalaxySimulation.o $(SIMOBJS)

# Object file generation rules
all: MyGalaxySimulation

MyGalaxySimulation : $(OBJS)
	$(CPP) $(PROFFLAGS) $(OBJS) -o MyGalaxySimulation

clean:
	rm MyGalaxySimulation *.o

# Object file generation rules
Event.o: Event.cpp Event.h
	$(CPP) $(CPPFLAGS) -c Event.cpp

EventQueue.o: EventQueue.cpp EventQueue.h Heap.h
	$(CPP) $(CPPFLAGS) -c EventQueue.cpp

ForceEvent.o: ForceEvent.cpp ForceEvent.h Event.h
	$(CPP) $(CPPFLAGS) -c ForceEvent.cpp

FrameEvent.o: FrameEvent.cpp FrameEvent.h Event.h
	$(CPP) $(CPPFLAGS) -c FrameEvent.cpp

GalaxySimulation.o: GalaxySimulation.cpp
	$(CPP) $(CPPFLAGS) -c GalaxySimulation.cpp

GlobularClusterPSF.o: GlobularClusterPSF.cpp GlobularClusterPSF.h ParticleSystemFactory.h
	$(CPP) $(CPPFLAGS) -c GlobularClusterPSF.cpp

GravityForce.o: GravityForce.cpp GravityForce.h Force.h
	$(CPP) $(CPPFLAGS) -c GravityForce.cpp

GravityPSF.o: GravityPSF.cpp GravityPSF.h ParticleSystemFactory.h
	$(CPP) $(CPPFLAGS) -c GravityPSF.cpp

Particle.o: Particle.cpp Particle.h
	$(CPP) $(CPPFLAGS) -c Particle.cpp

Point.o: Point.cpp Point.h Particle.h
	$(CPP) $(CPPFLAGS) -c Point.cpp

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<
