#ifndef TextureLoader
#define TextureLoader

#include "main.h"

class CTextureLoader {
public:
    CTextureLoader() = default;
    ~CTextureLoader();

    bool Load(const char* filePath, int width, int height);

    GLuint GetID() const { return ID; }
    int GetWidth() const { return WIDTH; }
    int GetHeight() const { return HEIGHT; }

private:

    GLuint ID;
    int WIDTH, HEIGHT;
};

#endif
