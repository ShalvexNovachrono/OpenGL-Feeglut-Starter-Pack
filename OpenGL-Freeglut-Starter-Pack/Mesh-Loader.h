#ifndef MeshLoader
#define MeshLoader
#include "main.h"
#include "File-Loader.h"
#include "Array.h"
#include "Maths.h"

struct Vertex {
    GLfloat x, y, z;
};

struct TextureCoordinates {
    GLfloat u, v;
};

struct Mesh {
    Vertex* vertices;
    Vec3* normals;
    GLushort* indices;
    TextureCoordinates* texCoords;
    int vertexCount, normalCount, texCoordCount, indexCount;
};

class CMeshLoader{
public:
    static Mesh* LoadMesh(const string& filename);
};


#endif
