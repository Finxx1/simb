#pragma once

typedef unsigned int Model;

Model load_model(const char* path);
void draw_model(Model model);