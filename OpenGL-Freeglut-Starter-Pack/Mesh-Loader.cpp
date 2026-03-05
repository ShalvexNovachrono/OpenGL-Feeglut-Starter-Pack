#include "Mesh-Loader.h"

static void LoadVertices(ifstream& content, Mesh& mesh) {
    content >> mesh.vertexCount;
    
    if (mesh.vertexCount > 0) { // check
        mesh.vertices = new Vertex[mesh.vertexCount]; // reserve space
        
        for (int i = 0; i < mesh.vertexCount; i++) {
            content >> mesh.vertices[i].x;
            content >> mesh.vertices[i].y;
            content >> mesh.vertices[i].z;
        }
        
    }
}

static void LoadTexture(ifstream& content, Mesh& mesh) {
    content >> mesh.texCoordCount;
    
    mesh.texCoords = new TextureCoordinates[mesh.texCoordCount];
    for (int i = 0; i < mesh.texCoordCount; i++) {
        content >> mesh.texCoords[i].u;
        content >> mesh.texCoords[i].v;
    }
}

static void LoadNormals(ifstream& content, Mesh& mesh) {
    content >> mesh.normalCount;
    
    mesh.normals = new Vec3[mesh.normalCount];
    for (int i = 0; i < mesh.normalCount; i++) {
        content >> mesh.normals[i].x;
        content >> mesh.normals[i].y;
        content >> mesh.normals[i].z;
    }
}

static void TriangulateFace(const Array::CArray<GLushort>& faceIndices, Array::CArray<GLushort>& outIndices) {
    if (faceIndices.Size() < 3) return;
    
    for (int i = 1; i < faceIndices.Size() - 1; ++i) {
        outIndices.Append(faceIndices[0]);
        outIndices.Append(faceIndices[i]);
        outIndices.Append(faceIndices[i + 1]);
    }
}


static void LoadIndices(ifstream& content, Mesh& mesh) {
    int faceCount;
    content >> faceCount;
    
    Array::CArray<GLushort> triangulatedIndices;
    
    for (int i = 0; i < faceCount; i++) {
        int verticesInFace;
        content >> verticesInFace; 
        
        Array::CArray<GLushort> faceIndices;
        for (int j = 0; j < verticesInFace; j++) {
            GLushort index;
            content >> index;
            faceIndices.Append(index);
        }
        
        TriangulateFace(faceIndices, triangulatedIndices);
    }
    
    mesh.indexCount = triangulatedIndices.Size();
    mesh.indices = new GLushort[mesh.indexCount];
    for (int i = 0; i < mesh.indexCount; i++) {
        mesh.indices[i] = triangulatedIndices[i];
    }
}

Mesh* CMeshLoader::LoadMesh(const string& filePath) {
    Mesh* mesh = new Mesh();
    
    ifstream content = std::move(CFileLoader::FileContent(filePath.c_str()));
    
    LoadVertices(content, *mesh);
    LoadTexture(content, *mesh);
    LoadNormals(content, *mesh);
    LoadIndices(content, *mesh);
    
    if (mesh->indexCount == 0 || mesh->vertexCount == 0 || mesh->texCoordCount == 0 || mesh->normalCount == 0) {
        LOG_WARNING("File is empty.")
        return nullptr;
    }
    
    LOG_DEBUG("Mesh loaded successfully.")
    
    content.close();
    
    return mesh;
}
