#pragma once

typedef unsigned int Texture2D;

Texture2D load_texture(const char* path);
void set_texture(Texture2D texture, int slot);