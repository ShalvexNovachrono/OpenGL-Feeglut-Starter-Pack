# OpenGL Freeglut Starter Pack
A lightweight C++ starter template for OpenGL development using Freeglut. This project provides a pre-configured environment with window management, a custom math library, and utility macros to jumpstart your OpenGL projects.

## Project Structure
- **`OpenGL-Freeglut-Starter-Pack/`**: Contains the source code and headers.
  - `Renderer-Window.cpp/h`: The main window and rendering logic (`CRendererWindow` class).
  - `Maths.h`: Custom math library (Vectors, Lerp, etc.).
  - `Input-Manager.cpp/h`: Handles keyboard and mouse input (`CInputManager` class).
  - `Asset-Manager.cpp/h`: Manages loading and retrieval of meshes and textures (`CAssetManager` class).
  - `Mesh-Loader.cpp/h`: Utility for loading 3D mesh data.
  - `Texture-Loader.cpp/h`: Utility for loading and managing OpenGL textures.
  - `main.h`: Common includes and logging macros.

## Where to Write Your Code
Most of your development will happen in `Renderer-Window.cpp`. Here are the key methods in the `CRendererWindow` class:

### 1. Initialization (`Start`)
Use the `Start()` method for any setup that needs to happen once when the application begins (e.g., loading textures, initializing game objects).
```cpp
void CRendererWindow::Start() {
    // Your initialization code here
}
```

### 2. Update Logic (`Timer`)
The `Timer()` method is called every frame. Use this for physics, movement, and logic updates. You can use `deltaTime` for frame-independent movement.
```cpp
void CRendererWindow::Timer() {
    // Your update logic here (e.g., position += velocity * deltaTime)
    
    // Note: The starter pack already handles deltaTime calculation 
    // and basic input state updates in this method.
}
```

### 3. Rendering (`Draw`)
The `Draw()` method is where all your OpenGL drawing commands should go.
```cpp
void CRendererWindow::Draw() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    // Your OpenGL drawing code here (e.g., glutSolidTeapot(1.0);)
    
    glPopMatrix();
    glutSwapBuffers();
}
```

## Features

### Asset Management (`CAssetManager`)
The `CAssetManager` allows you to load and retrieve meshes and textures efficiently.
- `assetManager->LoadMesh("name", "path/to/mesh.obj")`: Load a mesh file.
- `assetManager->GetMesh("name")`: Retrieve a loaded mesh.
- `assetManager->LoadTexture("name", "path/to/image.png", width, height)`: Load a texture.
- `assetManager->GetTexture("name")`: Retrieve a loaded texture.

### Math Library (`Maths.h`)
The project includes a custom math library with support for:
- **`Vec2`, `Vec3`, `Vec4`**: Vector classes with full operator overloading.
- **`LERP`**: Linear interpolation and `PingPong` functions.
- **Utility**: `DegreesToRadians`, `RadiansToDegrees`, `RandomNumber`, and string parsing.

Example:
```cpp
Vec3 position = Vec3(0, 0, 0);
Vec3 velocity = Vec3(10.0f, 0, 0);
position += velocity * GetDeltaTime();
```

### Input Management (`CInputManager`)
Access input via the `input` member in `CRendererWindow`:
- `input->IsDown(key)`: Check if a key is currently held.
- `input->WasPressed(key)`: Check if a key was pressed this frame.
- `input->GetMousePosition()`: Get current mouse coordinates.
- `input->GetMouseDelta()`: Get mouse movement since last frame.

### Logging (`main.h`)
Use these macros for colored console output:
- `LOG_DEBUG("message")`: Green output for general info.
- `LOG_WARNING("message")`: Yellow output for warnings.
- `LOG_ERROR("message")`: Red output (terminates application).

## Getting Started
1. Clone the repository.
2. Open `OpenGL-Feeglut-Starter-Pack.sln` in Visual Studio.
3. Ensure the configuration is set to **Debug x86** or **Release x86** (Freeglut is configured for x86 in this pack).
4. Build and Run (F5).
