#pragma once

typedef unsigned int Shader;

Shader load_shader(const char* path);
void set_shader(Shader shader);