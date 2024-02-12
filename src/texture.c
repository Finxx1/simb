#include <glad/glad.h>
#include <ktx.h>

#include "simb.h"
#include "texture.h"

Texture2D load_texture(const char* path) {
    ktxTexture* tex;
    Texture2D r = 0;
    GLenum target, error;

    KTX_error_code code = ktxTexture_CreateFromNamedFile(path, KTX_TEXTURE_CREATE_NO_FLAGS, &tex);
    if (code != KTX_SUCCESS) die("failed to load texture '%s'", path);

    code = ktxTexture_GLUpload(tex, &r, &target, &error);
    if (code != KTX_SUCCESS) die("failed to upload texture");

    ktxTexture_Destroy(tex);

    if (r == 0) die("failed to load texture");

    return r;
}

void set_texture(Texture2D texture, int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texture);
    unsigned int current;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&current);
    glUniform1i(glGetUniformLocation(current, "tex"), slot);
}