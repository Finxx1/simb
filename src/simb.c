#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "simb.h"

#include "camera.h"
#include "sky.h"
#include "shader.h"
#include "model.h"
#include "texture.h"
#include "scene.h"

GLFWwindow* window;
Scene* scene;

void init_gl() {
    if (!glfwInit()) die("failed to initialize glfw");

    window = glfwCreateWindow(800, 450, "Simb", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) die("failed to initialize glad");

    glEnable(GL_DEPTH_TEST);
}

int main() {
    init_gl();
    scene = init_scene(window);
    set_sky(scene, "sky");

    glClearColor(0.0, 0.0, 0.0, 1.0);

    double t1 = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        update_scene(scene);
        draw_scene(scene);

        glfwPollEvents();

        glfwSwapBuffers(window);

        while (glfwGetTime() < t1 + 1.0/60.0);
        t1 = glfwGetTime();
    }

    free_scene(scene);
    glfwTerminate();

    return 0;
}
