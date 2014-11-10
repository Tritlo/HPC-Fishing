#!/bin/env python

###
# This script renders the output file.
# Simply cat each tick into this file
# to see the output. There is also
# a script that is included that renders
# each tick with a single command.
###
import sys
import math

import struct

def rI(f):
    return struct.unpack('i',f.read(4))

def getDataData(datafilename="dataoutput",datalength=4):
    lis = []
    with open(datafilename,"rb") as f:
        for i in range(datalength):
            lis.append(rI(f)[0])
    return tupToDataData(lis)

def tupToDataData(tup):
    return dict(zip(["numticks","numprocs","totaltickstofull","numcaptains"],tup))



def capTupToData(tup):
    return dict(zip(["tick","capnum","rank","caughtfishes","othercaptaincaughtfishes"],tup))

def getCapData(filename="captainsoutput",datalength=5):
    lines = []
    with open(filename,"rb") as f:
        while True:
            try:
                lis = []
                for i in range(datalength):
                    lis.append(rI(f)[0])
                lines.append(capTupToData(lis))
            except:
                return lines



def getFishData(filename="fishoutput",datalength=7):
    lines = []
    with open(filename,"rb") as f:
        while True:
            try:
                lis = []
                for i in range(datalength):
                    lis.append(rI(f)[0])
                lines.append(fishTupToData(lis))
            except:
                return lines

def fishTupToData(lis):
    coords = []
    coords.append(lis[2])
    coords.append(lis[3])
    i = int(coords[0])
    j = int(coords[1])
    obj = {"tick": lis[0],
           "rank": lis[1],
           "coords":(i,j),
           "iscaptain":bool(lis[4]),
           "spawned":bool(lis[5]),
           "numfishes":lis[6]
          }
    return obj

if(len(sys.argv) > 1):
    dataData = getDataData(sys.argv[1])
    capData = getCapData(sys.argv[2])
    fishData = getFishData(sys.argv[3])
else:
    dataData = getDataData()
    capData =  getCapData()
    fishData = getFishData()

numprocs = dataData["numprocs"]
numticks = dataData["numticks"]


print dataData
def color(s,colname):
    return colname+s+"\033[0m"

for tick in range(numticks):
    ran = range(int(math.sqrt(numprocs)))
    map = [["." for j in ran] for i in ran]
    tickobjs = [obj for obj in fishData if obj["tick"] is tick]
    captainslog = [line for line in capData if line["tick"] is tick]

    for obj in tickobjs:
        i,j = obj["coords"]
        fish = str(obj["numfishes"])
        if obj["iscaptain"]:
            map[j][i] = color("X","\033[91m")
        elif obj["spawned"]:
            map[j][i] = color(fish,"\033[92m")
        else:
            map[j][i] = fish



    if len(captainslog) > 0:
        print "Captains log:"
    print "Tick %d" % (tick,)
    for entry in captainslog:
        print "Captain %(capnum)s: I have caught %(caughtfishes)s fishes, but I hear the other captain has caught %(othercaptaincaughtfishes)s fishes." % entry

    for line in map:
        stri = ""
        for cell in line:
            stri += cell + " "
        print stri

    print ""
print "Avg num ticks to fill nets %.2f" %( dataData["totaltickstofull"]/(float(dataData["numcaptains"])),)
