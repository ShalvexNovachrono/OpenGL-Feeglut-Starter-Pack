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
  - `Thread-Manager.cpp/h`: Manages a thread pool for asynchronous task execution (`CThreadManager` class).
  - `Array.h`: Custom dynamic array implementation (`CArray` class).
  - `KeyValue.h`: Custom key-value pair container (`CKeyValue` class).
  - `File-Loader.cpp/h`: Utility for reading file contents.
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

**Loading Assets:**
```cpp
// In Start() or a loading function
assetManager->LoadMesh("teapot", "Assets/Meshes/teapot.obj");
assetManager->LoadTexture("brick", "Assets/Textures/brick.png", 512, 512); // width and height are optional
```

**Retrieving Assets:**
```cpp
// In Draw() or any rendering function
CMesh* teapotMesh = assetManager->GetMesh("teapot");
CTexture* brickTexture = assetManager->GetTexture("brick");

if (teapotMesh) {
    // Use teapotMesh for rendering
}
if (brickTexture) {
    // Bind brickTexture
}
```

### Thread Management (`CThreadManager`)
The `CThreadManager` provides a thread pool for asynchronous task execution, allowing you to offload heavy computations without blocking the main thread.

**Basic Usage:**
```cpp
// In your class, typically as a member variable
CThreadManager threadManager; 

// Enqueue a task (e.g., in Start() or a game logic function)
// The task will run asynchronously in one of the thread pool's worker threads.
threadManager.Enqueue([]() {
    LOG_DEBUG("Performing a heavy computation in a background thread...");
    // Simulate work
    this_thread::sleep_for(chrono::seconds(2)); 
    LOG_DEBUG("Computation complete!");
});

// If you need to wait for all enqueued tasks to finish (e.g., before exiting)
// This will block the calling thread until all tasks are done.
threadManager.WaitAll(); 
```

**Enqueueing tasks that return values:**
You can use `std::async` in conjunction with `Enqueue` if you need to retrieve a result from an asynchronous task.
```cpp
// Example: Calculate something and get the result later
std::future<int> futureResult = threadManager.Enqueue([]() {
    LOG_DEBUG("Calculating sum in background...");
    int sum = 0;
    for (int i = 0; i < 1000000; ++i) {
        sum += i;
    }
    return sum;
});

// Later, when you need the result (this will block until the task is complete)
int result = futureResult.get();
LOG_DEBUG("Calculated sum: " + to_string(result));
```

### Custom Containers (`CArray` & `CKeyValue`)
Lightweight alternatives to STL containers:
- **`CArray<T>`**: A dynamic array with `Append`, `RemoveAt`, and iterator support.
- **`CKeyValue<K, V>`**: A simple dictionary/map implementation built on `CArray`. (not very fast for large collections)

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

#### Keyboard & Mouse
- `input->IsDown(key)`: Check if a key is currently held.
- `input->WasPressed(key)`: Check if a key was pressed this frame.
- `input->WasReleased(key)`: Check if a key was released this frame.
- `input->IsMouseButtonDown(button)`: Check if a mouse button (0-2) is held.
- `input->GetMousePosition()`: Get current mouse coordinates (`Vec2`).
- `input->GetMouseDelta()`: Get mouse movement since last frame (`Vec2`).
- `input->GetMouseWheelDelta()`: Get scroll wheel movement.

#### Input Actions (Delta Actions)
Define actions mapped to key pairs (e.g., 'A' and 'D') to get smoothed delta values for movement:
```cpp
// In Start()
input->AddDeltaInputAction("Horizontal", { 'a', 'd' });

// In Timer()
float move = input->GetDeltaInputAction("Horizontal");
position.x += move * GetDeltaTime();
```

### Logging (`main.h`)
The project provides several macros for colored console output and basic debugging:
- `LOG_DEBUG("message")`: Green output for general information.
- `LOG_DEBUG_R("message")`: Green output that overwrites the current console line (useful for counters).
- `LOG_WARNING("message")`: Yellow output for warnings.
- `LOG_ERROR("message")`: Red output for non-fatal errors.
- `LOG_FATAL("message")`: Red output for fatal errors; calls `exit(EXIT_FAILURE)`.
- `print(message)`: A simple macro for standard console output.

Example:
```cpp
LOG_DEBUG("Texture loaded successfully!");
if (x < 0) LOG_WARNING("Value is negative.");
```

## Getting Started
1. Clone the repository.
2. Open `OpenGL-Feeglut-Starter-Pack.sln` in Visual Studio.
3. Ensure the configuration is set to **Debug x86** or **Release x86** (Freeglut is configured for x86 in this pack).
4. Build and Run (F5).


## Resources
1. Wavefront (.obj) loader: https://www.scratchapixel.com/lessons/3d-basic-rendering/obj-file-format/obj-file-format.html