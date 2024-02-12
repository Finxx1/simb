#!/usr/bin/python3
# Run this file from the project directory, not tools/
# Args: ./tools/jpg2ktx.py ex
# Reads ./models/ex/albedo.jpg and makes ./models/ex_albedo.ktx

import sys
import os

ktx_invoke = "./tools/ktx create --format R8G8B8A8_UNORM "

os.system(ktx_invoke + "models/" + sys.argv[1] + "_src/albedo.jpg " + "models/" + sys.argv[1] + "_albedo.ktx")