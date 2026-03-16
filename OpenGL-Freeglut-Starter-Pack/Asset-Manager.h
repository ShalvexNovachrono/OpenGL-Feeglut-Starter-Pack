#ifndef AssetManager
#define AssetManager
#include "KeyValue.h"
#include "main.h"
#include "Mesh-Loader.h"
#include "Texture-Loader.h"

class CAssetManager {
private:
    CKeyValue<string, Mesh*> meshCollection;
    CKeyValue<string, CTextureLoader*> textureCollection;
public:
    CAssetManager() = default;
    ~CAssetManager();
    
    void LoadMesh(const string& meshName, const string& meshFilePath);
    void LoadMeshFromObj(const string& meshName, const string& meshFilePath);
    void LoadTexture(const string& textureName, const string& textureFilePath, int width, int height);
    Mesh* GetMesh(const string& meshName);
    CTextureLoader* GetTexture(const string& textureName);
};

#endif
