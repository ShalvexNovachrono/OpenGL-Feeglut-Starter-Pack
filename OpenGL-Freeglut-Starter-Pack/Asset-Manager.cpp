#define STB_IMAGE_IMPLEMENTATION 
#define MINIAUDIO_IMPLEMENTATION
#include "Asset-Manager.h"
#include "stb_image.h"
#include "miniaudio.h"

CAssetManager::CAssetManager() {
    ma_engine_init(nullptr, &audioEngine);
}

CAssetManager::~CAssetManager() {
    threadManager.WaitAll(); 
    
    audioCollection.clear();
    
    meshCollection.Clear();
    textureCollection.Clear();
    
    ma_engine_uninit(&audioEngine);
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

void CAssetManager::LoadAudio(const string& audioName, const string& audioFilePath) {
    LoadAudioAsync(audioName, audioFilePath).wait();
}

future<void> CAssetManager::LoadAudioAsync(const string& audioName, const string& audioFilePath) {
    return threadManager.Enqueue([this, audioName, audioFilePath] {
        ma_sound* sound = new ma_sound();
        ma_sound_init_from_file(&audioEngine, audioFilePath.c_str(), 0, nullptr, nullptr, sound);
        lock_guard<mutex> lock(audioMutex);
        audioCollection[audioName] = sound;
    });
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

ma_sound* CAssetManager::GetAudio(const string& audioName) {
    lock_guard<mutex> lock(audioMutex);
    auto it = audioCollection.find(audioName);
    if (it == audioCollection.end()) {
        LOG_WARNING("Audio not found: " + audioName)
        return nullptr;
    }
    return it->second;
}
