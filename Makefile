libs = ktx.lib glfw3_mt.lib glad.lib opengl32.lib user32.lib gdi32.lib shell32.lib kernel32.lib

all:
	$(CC) /MT src/*.c /I include /Fo: obj/ /link /LIBPATH:lib $(libs) /OUT:bin/simb.exe

generate:
	./tools/obj2mdl.py sky
	./tools/exr2ktx.py sky

.phony:
	