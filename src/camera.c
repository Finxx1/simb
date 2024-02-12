#include <cglm/cglm.h>
#include <glad/glad.h>

#include <stdlib.h>
#include <string.h>

#include "simb.h"
#include "camera.h"

typedef struct Camera {
    mat4 projection;
    vec4 pos;
    vec3 rot;
} Camera;

Camera* init_camera() {
    Camera* r = calloc(sizeof(Camera), 1);
    glm_perspective(glm_rad(90), 16.0/9.0, 0.1, 100.0, r->projection);
    glm_vec4_zero(r->pos);
    glm_vec3_zero(r->rot);

    return r;
}

void set_camera_pos(Camera* cam, float x, float y, float z) {
    cam->pos[0] = x;
    cam->pos[1] = y;
    cam->pos[2] = z;
}

void set_camera_rot(Camera* cam, float x, float y, float z) {
    cam->rot[0] = glm_rad(x);
    cam->rot[1] = glm_rad(y);
    cam->rot[2] = glm_rad(z);
}

void set_camera(Camera* cam) {
    mat4 rot2;
    glm_euler_zyx(cam->rot, rot2);

    unsigned int current;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&current);
    glUniform4fv(glGetUniformLocation(current, "pos"), 1, cam->pos);
    glUniformMatrix4fv(glGetUniformLocation(current, "rot"), 1, GL_FALSE, rot2[0]);
    glUniformMatrix4fv(glGetUniformLocation(current, "proj"), 1, GL_FALSE, cam->projection[0]);
}
