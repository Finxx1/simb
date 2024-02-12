#include <glad/glad.h>
#include <stdio.h>

#include "simb.h"
#include "model.h"

Model load_model(const char* path) {
    FILE* fp = fopen(path, "rb");
    if (!fp) die("failed to load model '%s'", path);

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    float* data = malloc(size);
    if (!data) die("failed to alloc %d bytes", size);
    
    if (fread(data, 1, size, fp) != size) die("failed to read model file");

    fclose(fp);

    Model r;
    glGenBuffers(1, &r);
    if (!r) die("failed to generate opengl buffer");

    glBindBuffer(GL_ARRAY_BUFFER, r);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    return r;
}

void draw_model(Model model) {
    glBindBuffer(GL_ARRAY_BUFFER, model);

    unsigned int size;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

	glDrawArrays(GL_TRIANGLES, 0, size / 20);
}
