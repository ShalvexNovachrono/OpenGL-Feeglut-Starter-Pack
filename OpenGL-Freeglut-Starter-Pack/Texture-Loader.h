#ifndef TextureLoader
#define TextureLoader

#include "main.h"

struct TextureData {
    unsigned char* pixels = nullptr;
    int width = 0;
    int height = 0;
    int channels = 0;

    bool IsValid() const { return pixels != nullptr; }
};

class CTextureLoader {
public:
    /// <summary>
    /// Default constructor for CTextureLoader.
    /// </summary>
    CTextureLoader() = default;

    /// <summary>
    /// Destructor for CTextureLoader. Deletes the OpenGL texture.
    /// </summary>
    ~CTextureLoader();

    /// <summary>
    /// Loads pixel data from disk. Safe to call from any thread.
    /// Does not touch OpenGL.
    /// </summary>
    static TextureData LoadFromDisk(const char* filePath);

    /// <summary>
    /// Uploads pixel data to the GPU. Must be called on the main thread.
    /// </summary>
    bool UploadToGPU(const TextureData& data);
    
    /// <summary>
    /// Loads a texture from the specified file path.
    /// </summary>
    /// <param name="filePath">The path to the texture file.</param>
    /// <param name="width">The desired width of the texture.</param>
    /// <param name="height">The desired height of the texture.</param>
    /// <returns>True if the texture was loaded successfully, false otherwise.</returns>
    bool Load(const char* filePath, int width, int height);
    
    /// <summary>
    /// Gets the OpenGL texture ID.
    /// </summary>
    /// <returns>The OpenGL texture ID.</returns>
    GLuint GetID() const { return ID; }

    /// <summary>
    /// Gets the width of the loaded texture.
    /// </summary>
    /// <returns>The width of the texture.</returns>
    int GetWidth() const { return WIDTH; }

    /// <summary>
    /// Gets the height of the loaded texture.
    /// </summary>
    /// <returns>The height of the texture.</returns>
    int GetHeight() const { return HEIGHT; }

private:
    GLuint ID;
    int WIDTH, HEIGHT;
};

#endif
