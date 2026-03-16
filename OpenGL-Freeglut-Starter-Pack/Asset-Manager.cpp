#include "Asset-Manager.h"
// to me: if #include <map> is used change Clear to clear
// to me: if #include <map> is used change value to second

CAssetManager::~CAssetManager() {
    meshCollection.Clear(); 
    textureCollection.Clear();
}

void CAssetManager::LoadMesh(const string& meshName, const string& meshFilePath) {
    Mesh* mesh = CMeshLoader::LoadMesh(meshFilePath);
    meshCollection[meshName] = mesh; 
}

void CAssetManager::LoadMeshFromObj(const string& meshName, const string& meshFilePath) {
    Mesh* mesh = CMeshLoader::LoadMeshFromObj(meshFilePath);
    meshCollection[meshName] = mesh;
}

void CAssetManager::LoadTexture(const string& textureName, const string& textureFilePath, int width, int height) {
    CTextureLoader* texture = new CTextureLoader();
    texture->Load(textureFilePath.c_str(), width, height);
    textureCollection[textureName] = texture;
}

Mesh* CAssetManager::GetMesh(const string& meshName) {
    auto it = meshCollection.find(meshName);
    if (it == meshCollection.end()) {
        LOG_WARNING("Mesh not found: " + meshName)
        return nullptr;
    }
    return it->value;
}

CTextureLoader* CAssetManager::GetTexture(const string& textureName) {
    auto it = textureCollection.find(textureName);
    if (it == textureCollection.end()) {
        LOG_WARNING("Texture not found: " + textureName)
        return nullptr;
    }
    return it->value;
}
