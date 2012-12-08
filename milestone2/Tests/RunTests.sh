#!/bin/sh

for i in {1..5}; do
   ../MyGalaxySimulation < Test$i.in > Test$i.my.out
   ../GalaxySimulation < Test$i.in > Test$i.out
   vimdiff Test$i.my.out Test$i.out
   rm Test$i.my.out Test$i.out
done
