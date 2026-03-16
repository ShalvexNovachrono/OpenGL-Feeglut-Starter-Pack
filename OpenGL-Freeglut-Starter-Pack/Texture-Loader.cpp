#define STB_IMAGE_IMPLEMENTATION  
#include "Texture-Loader.h"
#include "stb_image.h"

CTextureLoader::~CTextureLoader() {
    glDeleteTextures(1, &ID);
}

bool CTextureLoader::Load(const char* filePath, int width, int height) {
    // Load image using stb_image
    int channels;
    unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

    if (!data) {
        B_LOG_WARNING("Failed to load texture: " << filePath)
        B_LOG_WARNING("Reason: " << stbi_failure_reason())
        return false;
    }

    // Generate OpenGL texture
    glGenTextures(1, &ID);
    if (ID == 0) {
        B_LOG_WARNING("Failed to generate OpenGL texture ID.")
        stbi_image_free(data);
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, ID);

    // Determine format based on channels
    GLenum format;
    switch (channels) {
    case 1: format = GL_LUMINANCE; break;
    case 3: format = GL_RGB; break;
    case 4: format = GL_RGBA; break;
    default:
        B_LOG_WARNING("Unexpected number of channels: " << channels)
        format = GL_RGB;
        break;
    }

    // Upload texture data
    glTexImage2D(
        GL_TEXTURE_2D, 0, static_cast<GLint>(format),
        width, height, 0, format, GL_UNSIGNED_BYTE, data
    );

    // Check for OpenGL errors during texture upload
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        B_LOG_ERROR("OpenGL Error during texture upload: " << error)
        stbi_image_free(data);
        return false;
    }

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Clean up
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}
