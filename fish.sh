#!/bin/sh
#PBS -N Fishing
#PBS -lnodes=25
#PBS -M mpg3@hi.is
#PBS -m abe
#PBS -p 0
#PBS -d /home/mpg3/fish
mpirun /home/mpg3/fish/fishing
