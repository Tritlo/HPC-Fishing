#!/bin/sh
#PBS -N Fishing
#PBS -lnodes=16
#PBS -M mpg3@hi.is
#PBS -m abe
#PBS -o /home/mpg3/fish/
#PBS -p 0
mpirun /home/mpg3/fish/fishing
