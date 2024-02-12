#include <glad/glad.h>

#include <stdio.h>

#include "simb.h"
#include "texture.h"
#include "shader.h"
#include "model.h"

static Shader skyShader;
static Texture2D skyTexture;
static Model skyModel;

void init_sky(const char* path) {
    // Windows has no asprintf(). Sad.
    int albedosize = snprintf(NULL, 0, "models/%s_albedo.ktx", path);
    char* albedo = malloc(albedosize + 1);
    if (!albedo) die("failed to alloc %d bytes", albedosize + 1);
    sprintf(albedo, "models/%s_albedo.ktx", path);

    int modelsize = snprintf(NULL, 0, "models/%s.mdl", path);
    char* model = malloc(modelsize + 1);
    if (!model) die("failed to alloc %d bytes", modelsize + 1);
    sprintf(model, "models/%s.mdl", path);
    
    skyTexture = load_texture(albedo);
    skyModel = load_model(model);
    skyShader = load_shader("shaders/textured.glsl");

    free(albedo);
    free(model);
}

void draw_sky() {
    set_shader(skyShader);
    set_texture(skyTexture, 0);
    draw_model(skyModel);
}
