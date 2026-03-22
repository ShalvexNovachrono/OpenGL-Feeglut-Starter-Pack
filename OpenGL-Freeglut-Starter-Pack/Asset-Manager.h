#ifndef AssetManager
#define AssetManager
#include "KeyValue.h"
#include "main.h"
#include "Mesh-Loader.h"
#include "Thread-Manager.h"
#include "Texture-Loader.h"

struct PendingTexture {
    string name;
    CTextureLoader* loader;
    TextureData data;
};

class CAssetManager {
private:
    mutex meshMutex;
    mutex textureMutex;
    mutex pendingMutex;
    
    CKeyValue<string, Mesh*> meshCollection;
    CKeyValue<string, CTextureLoader*> textureCollection;
    
    CArray<PendingTexture> pendingTextures;
    
    CArray<thread> activeThreads;
    CThreadManager threadManager; 
public:
    /// <summary>
    /// Default constructor for CAssetManager.
    /// </summary>
    CAssetManager() = default;

    /// <summary>
    /// Destructor for CAssetManager. Cleans up allocated resources.
    /// </summary>
    ~CAssetManager();
    
    /// <summary>
    /// Loads a mesh synchronously.
    /// </summary>
    /// <param name="meshName">The name to associate with the loaded mesh.</param>
    /// <param name="meshFilePath">The file path of the mesh to load.</param>
    void LoadMesh(const string& meshName, const string& meshFilePath);

    /// <summary>
    /// Loads a mesh asynchronously using the thread manager.
    /// </summary>
    /// <param name="meshName">The name to associate with the loaded mesh.</param>
    /// <param name="meshFilePath">The file path of the mesh to load.</param>
    future<void>  LoadMeshAsync(const string& meshName, const string& meshFilePath);
    
    /// <summary>
    /// Loads a mesh from an OBJ file synchronously.
    /// </summary>
    /// <param name="meshName">The name to associate with the loaded mesh.</param>
    /// <param name="meshFilePath">The file path of the OBJ mesh to load.</param>
    void LoadMeshFromObj(const string& meshName, const string& meshFilePath);

    /// <summary>
    /// Loads a mesh from an OBJ file asynchronously using the thread manager.
    /// </summary>
    /// <param name="meshName">The name to associate with the loaded mesh.</param>
    /// <param name="meshFilePath">The file path of the OBJ mesh to load.</param>
    future<void> LoadMeshFromObjAsync(const string& meshName, const string& meshFilePath);
    
    /// <summary>
    /// Loads a texture synchronously.
    /// </summary>
    /// <param name="textureName">The name to associate with the loaded texture.</param>
    /// <param name="textureFilePath">The file path of the texture to load.</param>
    /// <param name="width">The width of the texture.</param>
    /// <param name="height">The height of the texture.</param>
    void LoadTexture(const string& textureName, const string& textureFilePath, int width, int height);

    /// <summary>
    /// Loads a texture asynchronously using the thread manager.
    /// </summary>
    /// <param name="textureName">The name to associate with the loaded texture.</param>
    /// <param name="textureFilePath">The file path of the texture to load.</param>
    /// <param name="width">The width of the texture.</param>
    /// <param name="height">The height of the texture.</param>
    future<void>  LoadTextureAsync(const string& textureName, const string& textureFilePath, int width, int height);
    
    /// <summary>
    /// Uploads any textures whose pixel data has finished loading.
    /// Must be called from the main thread once per frame.
    /// </summary>
    void UploadPendingTextures();
    
    /// <summary>
    /// Retrieves a loaded mesh by its name.
    /// </summary>
    /// <param name="meshName">The name of the mesh to retrieve.</param>
    /// <returns>A pointer to the Mesh object, or nullptr if not found.</returns>
    Mesh* GetMesh(const string& meshName);

    /// <summary>
    /// Retrieves a loaded texture by its name.
    /// </summary>
    /// <param name="textureName">The name of the texture to retrieve.</param>
    /// <returns>A pointer to the CTextureLoader object, or nullptr if not found.</returns>
    CTextureLoader* GetTexture(const string& textureName);
};

#endif
