#include "Texture-Loader.h"
#include "stb_image.h"

CTextureLoader::~CTextureLoader() {
    if (ID != 0) glDeleteTextures(1, &ID);
}

TextureData CTextureLoader::LoadFromDisk(const char* filePath) {
    TextureData data;
    data.pixels = stbi_load(
        filePath, &data.width, &data.height, &data.channels, 0
    );
    if (!data.pixels) {
        B_LOG_WARNING("Failed to load texture: " << filePath)
        B_LOG_WARNING("Reason: " << stbi_failure_reason())
    }
    return data;
}

bool CTextureLoader::UploadToGPU(const TextureData& data) {
    if (!data.IsValid()) return false;

    glGenTextures(1, &ID);
    if (ID == 0) {
        B_LOG_WARNING("Failed to generate OpenGL texture ID.")
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, ID);

    GLenum format;
    switch (data.channels) {
    case 1: format = GL_LUMINANCE; break;
    case 3: format = GL_RGB;       break;
    case 4: format = GL_RGBA;      break;
    default:
        B_LOG_WARNING("Unexpected number of channels: " << data.channels)
        format = GL_RGB;
        break;
    }

    WIDTH  = data.width;
    HEIGHT = data.height;

    glTexImage2D(
        GL_TEXTURE_2D, 0, static_cast<GLint>(format),
        data.width, data.height, 0,
        format, GL_UNSIGNED_BYTE, data.pixels
    );

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        B_LOG_ERROR("OpenGL error during texture upload: " << error)
        glBindTexture(GL_TEXTURE_2D, 0);
        return false;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

bool CTextureLoader::Load(const char* filePath, int width, int height) {
    TextureData data = LoadFromDisk(filePath);
    bool result = UploadToGPU(data);
    if (data.pixels) stbi_image_free(data.pixels);
    return result;
}
