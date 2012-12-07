#!/bin/sh

for i in {6..6}; do
   ../MyGalaxySimulation < Test$i.in > Test$i.my.out
   ../GalaxySimulationTell < Test$i.in > Test$i.out
   vimdiff Test$i.my.out Test$i.out
   rm Test$i.my.out Test$i.out
done
