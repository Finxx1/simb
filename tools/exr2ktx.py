#!/usr/bin/python3
# Run this file from the project directory, not tools/
# Args: ./tools/exr2ktx.py ex
# Reads ./models/ex/albedo.exr and makes ./models/ex_albedo.ktx

import sys
import os

ktx_invoke = "./tools/ktx create --format R16G16B16A16_SFLOAT "

os.system(ktx_invoke + "models/" + sys.argv[1] + "_src/albedo.exr " + "models/" + sys.argv[1] + "_albedo.ktx")