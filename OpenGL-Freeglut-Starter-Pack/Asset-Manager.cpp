#define STB_IMAGE_IMPLEMENTATION  
#include "Asset-Manager.h"
#include "stb_image.h"

CAssetManager::~CAssetManager() {
    threadManager.WaitAll(); 
    
    meshCollection.Clear();
    textureCollection.Clear();
}

void CAssetManager::LoadMesh(const string& meshName, const string& meshFilePath) {
    LoadMeshAsync(meshName, meshFilePath).wait();
}

future<void> CAssetManager::LoadMeshAsync(const string& meshName, const string& meshFilePath) {
    return threadManager.Enqueue([this, meshName, meshFilePath] {
        Mesh* mesh = CMeshLoader::LoadMesh(meshFilePath);
        lock_guard<mutex> lock(meshMutex);
        meshCollection[meshName] = mesh;
    });
}

void CAssetManager::LoadMeshFromObj(const string& meshName, const string& meshFilePath) {
    LoadMeshFromObjAsync(meshName, meshFilePath).wait();
}

future<void> CAssetManager::LoadMeshFromObjAsync(const string& meshName, const string& meshFilePath) {
    return threadManager.Enqueue([this, meshName, meshFilePath] {
        Mesh* mesh = CMeshLoader::LoadMeshFromObj(meshFilePath);
        lock_guard<mutex> lock(meshMutex);
        meshCollection[meshName] = mesh;
    });
}

void CAssetManager::LoadTexture(const string& textureName, const string& textureFilePath, int width, int height) {
    LoadTextureAsync(textureName, textureFilePath, width, height).wait();
}

future<void> CAssetManager::LoadTextureAsync(const string& textureName, const string& textureFilePath, int width, int height) {
    return threadManager.Enqueue([this, textureName, textureFilePath] {
        TextureData data = CTextureLoader::LoadFromDisk(
            textureFilePath.c_str()
        );
        auto* tex = new CTextureLoader();

        lock_guard<mutex> lock(pendingMutex);
        pendingTextures.Append({ textureName, tex, data });
    });
}

void CAssetManager::UploadPendingTextures() {
    lock_guard<mutex> lock(pendingMutex);
    for (int i = 0; i < pendingTextures.Size(); i++) {
        auto& pending = pendingTextures[i];
        pending.loader->UploadToGPU(pending.data);
        if (pending.data.pixels) stbi_image_free(pending.data.pixels);

        lock_guard<mutex> texLock(textureMutex);
        textureCollection[pending.name] = pending.loader;
    }
    pendingTextures.Clear();
}

Mesh* CAssetManager::GetMesh(const string& meshName) {
    lock_guard<mutex> lock(meshMutex);
    auto it = meshCollection.find(meshName);
    if (it == meshCollection.end()) {
        LOG_WARNING("Mesh not found: " + meshName)
        return nullptr;
    }
    return it->value;
}

CTextureLoader* CAssetManager::GetTexture(const string& textureName) {
    lock_guard<mutex> lock(textureMutex);
    auto it = textureCollection.find(textureName);
    if (it == textureCollection.end()) {
        LOG_WARNING("Texture not found: " + textureName)
        return nullptr;
    }
    return it->value;
}