#pragma once

typedef struct Scene Scene;

Scene* init_scene(void* window);
void set_sky(Scene* scene, const char* path);

void update_scene(Scene* scene);
void draw_scene(Scene* scene);

void free_scene(Scene* scene);