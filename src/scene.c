#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <math.h>

#include "camera.h"
#include "sky.h"
#include "boat.h"

#define RAD(x) ((x * 3.1415926535) / 180.0)

typedef struct Scene {
    GLFWwindow* window;

    Camera* cam;
    float cam_x, cam_y, cam_z, cam_pitch, cam_yaw;
} Scene;

Scene* init_scene(GLFWwindow* window) {
    Scene* r = calloc(sizeof(Scene), 1);

    r->cam = init_camera();
    r->window = window;

    init_boat();

    return r;
}

void set_sky(Scene* scene, const char* path) {
    init_sky(path);
}

void update_scene(Scene* scene) {
    if (glfwGetKey(scene->window, GLFW_KEY_W)) {
        scene->cam_x += sin(RAD(scene->cam_yaw)) * 0.1;
        scene->cam_z += cos(RAD(scene->cam_yaw)) * 0.1;
    }
    if (glfwGetKey(scene->window, GLFW_KEY_S)) {
        scene->cam_x -= sin(RAD(scene->cam_yaw)) * 0.1;
        scene->cam_z -= cos(RAD(scene->cam_yaw)) * 0.1;
    }
    if (glfwGetKey(scene->window, GLFW_KEY_A)) {
        scene->cam_x += cos(RAD(scene->cam_yaw)) * 0.1;
        scene->cam_z -= sin(RAD(scene->cam_yaw)) * 0.1;
    }
    if (glfwGetKey(scene->window, GLFW_KEY_D)) {
        scene->cam_x -= cos(RAD(scene->cam_yaw)) * 0.1;
        scene->cam_z += sin(RAD(scene->cam_yaw)) * 0.1;
    }

    if (glfwGetKey(scene->window, GLFW_KEY_UP)) scene->cam_pitch += 1.0;
    if (glfwGetKey(scene->window, GLFW_KEY_DOWN)) scene->cam_pitch -= 1.0;
    if (glfwGetKey(scene->window, GLFW_KEY_LEFT)) scene->cam_yaw += 1.0;
    if (glfwGetKey(scene->window, GLFW_KEY_RIGHT)) scene->cam_yaw -= 1.0;

    update_boat();
}

void draw_scene(Scene* scene) {
    set_camera_rot(scene->cam, scene->cam_pitch, scene->cam_yaw, 0);

    set_camera_pos(scene->cam, 0, 0, 0);
    set_camera(scene->cam);
    
    draw_sky();

    set_camera_pos(scene->cam, scene->cam_x, scene->cam_y, scene->cam_z);
    set_camera(scene->cam);

    draw_boat(scene->cam);
}

void free_scene(Scene* scene) {
    free(scene->cam);
    free(scene);
}
