#!/bin/sh

for i in {1..6}; do
   ../MyGalaxySimulation < Test$i.in > Test$i.my.out
   ../GalaxySimulation < Test$i.in > Test$i.out
   diff Test$i.my.out Test$i.out
   rm Test$i.my.out Test$i.out
done
