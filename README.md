# OpenGL Freeglut Starter Template

A minimal C++ OpenGL template with Freeglut. This project includes window management, asset loading, and custom containers to help you start quickly.

## What's Included

**Core**
- `Renderer-Window.cpp/h` - Main window class
- `Maths.h` - Vector types and math utilities
- `Input-Manager.cpp/h` - Keyboard and mouse input
- `main.h` - Logging macros and includes

**Assets**
- `Asset-Manager.cpp/h` - Load meshes, textures, and audio
- `Mesh-Loader.cpp/h` - OBJ and custom mesh loading
- `Texture-Loader.cpp/h` - Texture loading with stb_image

**Utilities**
- `Thread-Manager.cpp/h` - Worker thread pool
- `Array.h` - Dynamic array
- `Key-Value.h` - AVL tree map
- `File-Loader.cpp/h` - File reading helpers

## Basic Usage

### 1. Window and Rendering

Add your code in `Renderer-Window.cpp`:

```cpp
// Initial setup
void CRendererWindow::Start() {
    assetManager->LoadMesh("model", "./Assets/model.obj");
}

// Per-frame updates
void CRendererWindow::Timer() {
    worldRotation.y += deltaTime * 100.0f; // Rotate 100°/sec
}

// Drawing
void CRendererWindow::Draw() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Your OpenGL rendering here
}
```

### 2. Loading Assets

```cpp
// Meshes
assetManager->LoadMeshFromObj("zombie", "./Assets/zombie.obj");

// Textures
assetManager->LoadTexture("shrek", "./Assets/shrek.jpg", 0, 0);

// Audio
assetManager->LoadAudio("slap", "./Assets/slap.mp3");
```

### 3. Input Handling

```cpp
// Check keys
if (input->WasPressed('E')) {
    // Play sound when E is pressed
    ma_sound* sound = assetManager->GetAudio("slap");
    if (sound) ma_sound_start(sound);
}

// Smooth movement
input->AddDeltaInputAction("Vertical", {'W', 'S'});
float move = input->GetDeltaInputAction("Vertical");
worldPosition.z += move * deltaTime;
```

### 4. Thread Pool

```cpp
// Run task in background
threadManager.Enqueue([]() {
    // Heavy computation here
    LOG_DEBUG("Task complete");
});
```

## Getting Started
1. Open `OpenGL-Freeglut-Starter-Pack.sln` in Visual Studio
2. Set to Debug x86 or Release x86
3. Build and Run (F5)

## Dependencies
- Freeglut (x86, included)
- miniaudio (for sound)
- stb_image (for textures)
