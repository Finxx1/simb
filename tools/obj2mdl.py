#!/usr/bin/python3
# Run this file from the project directory, not tools/
# Args: ./tools/obj2mdl.py ex
# Reads ./models/ex.obj and makes ./models/ex.mdl

import sys
import struct
import os

fp = open("models/" + sys.argv[1] + "_src/obj.obj", "rb")
filedata = fp.read()
filestr = filedata.decode('utf-8')

vdata = filestr[filestr.index('v'):filestr.index('vn')-1]
vxdata = vdata.split('\n')

vtdata = filestr[filestr.index('vt'):filestr.index('s')-1]
vtxdata = vtdata.split('\n')

verticies = []
indices = []

vts = []
vtindices = []

for vxline in vxdata:
    vxxline = vxline.split(' ')
    verticies.append(float(vxxline[1]))
    verticies.append(float(vxxline[2]))
    verticies.append(float(vxxline[3]))

for vtline in vtxdata:
    vtxxline = vtline.split(' ')
    vts.append(float(vtxxline[1]))
    vts.append(float(vtxxline[2]))

fdata = filestr[filestr.index('f'):-1]
fxdata = fdata.split()

for i in range(fxdata.count('f')):
    fxdata.remove('f')

for fxline in fxdata:
    fxxline = fxline.split('/')
    indices.append(int(fxxline[0]) - 1)
    vtindices.append(int(fxxline[1]) - 1)

of = open("models/" + sys.argv[1] + ".mdl", "wb")

for i in range(len(indices)):
    of.write(struct.pack("<f", verticies[indices[i] * 3]))
    of.write(struct.pack("<f", verticies[indices[i] * 3 + 1]))
    of.write(struct.pack("<f", verticies[indices[i] * 3 + 2]))
    of.write(struct.pack("<f", vts[vtindices[i] * 2]))
    of.write(struct.pack("<f", vts[vtindices[i] * 2 + 1]))