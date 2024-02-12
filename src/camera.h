#pragma once

typedef struct Camera Camera;

Camera* init_camera();
void set_camera_pos(Camera* cam, float x, float y, float z);
void set_camera_rot(Camera* cam, float x, float y, float z);
void set_camera(Camera* cam);