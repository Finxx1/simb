#include <glad/glad.h>
#include <stdio.h>

#include "simb.h"
#include "shader.h"

Shader load_shader(const char* path) {
    FILE* fp = fopen(path, "rb");
    if (!fp) die("failed to load shader '%s'", path);

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* data = malloc(size + 1);
    if (!data) die("failed to alloc %d bytes", size + 1);
    data[size] = 0;
    
    if (fread(data, 1, size, fp) != size) die("failed to read shader file");

    fclose(fp);

    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    if (!vert) die("failed to create vertex shader");

    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    if (!vert) die("failed to create fragment shader");

    char* vertsource[] = {"#version 460\n#define VERT\n", data};
    glShaderSource(vert, 2, vertsource, NULL);

    char* fragsource[] = {"#version 460\n#define FRAG\n", data};
    glShaderSource(frag, 2, fragsource, NULL);

    free(data);

    glCompileShader(vert);

    unsigned int success;
    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        unsigned int length;
        glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &length);

        char* log = calloc(length + 1, 1);
        glGetShaderInfoLog(vert, length, &length, log);

        glDeleteShader(vert);

        die("vert shader failed to compile. log:\n%s", log);
    }

    glCompileShader(frag);

    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        unsigned int length;
        glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &length);

        char* log = calloc(length + 1, 1);
        glGetShaderInfoLog(frag, length, &length, log);

        glDeleteShader(frag);

        die("frag shader failed to compile. log:\n%s", log);
    }

    Shader r = glCreateProgram();

    glAttachShader(r, vert);
    glAttachShader(r, frag);

    glLinkProgram(r);

    glGetProgramiv(r, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        unsigned int length;
        glGetProgramiv(r, GL_INFO_LOG_LENGTH, &length);

        char* log = calloc(length + 1, 1);
        glGetProgramInfoLog(r, length, &length, log);

        glDeleteProgram(r);

        die("shader failed to link. log:\n%s", log);
    }

    glDetachShader(r, vert);
    glDetachShader(r, frag);

    glDeleteShader(vert);
    glDeleteShader(frag);

    return r;
}

void set_shader(Shader shader) {
    glUseProgram(shader);
}
