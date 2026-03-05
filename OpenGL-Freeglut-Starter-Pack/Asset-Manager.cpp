#include "Asset-Manager.h"

CAssetManager::~CAssetManager() {
    meshCollection.clear();
    textureCollection.clear();
}

void CAssetManager::LoadMesh(const string& meshName, const string& meshFilePath) {
    Mesh* mesh = CMeshLoader::LoadMesh(meshFilePath);
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
        LOG_WARNING("Mesh not found.")
        return meshCollection["default"];
    }
    return it->second;
}

CTextureLoader* CAssetManager::GetTexture(const string& textureName) {
    auto it = textureCollection.find(textureName);
    if (it == textureCollection.end()) {
        LOG_WARNING("Texture not found.")
        return textureCollection["default"];
    }
    return it->second;
}
