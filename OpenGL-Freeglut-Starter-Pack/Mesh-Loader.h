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
    /// <summary>
    /// Loads a mesh from a custom binary file format.
    /// </summary>
    /// <param name="filename">The path to the mesh file.</param>
    /// <returns>A pointer to the loaded Mesh object, or nullptr if loading fails.</returns>
    static Mesh* LoadMesh(const string& filename);
    
    /// <summary>
    /// Loads a mesh from an OBJ file.
    /// </summary>
    /// <param name="filename">The path to the OBJ file.</param>
    /// <returns>A pointer to the loaded Mesh object, or nullptr if loading fails.</returns>
    static Mesh* LoadMeshFromObj(const string& filename);
};


#endif
