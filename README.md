# OpenGL Freeglut Starter Pack
A lightweight C++ starter template for OpenGL development using Freeglut. This project provides a pre-configured environment with window management, a custom math library, and utility macros to jumpstart your OpenGL projects.

## Where to Write Your Code
Most of your development will happen in `Renderer-Window.cpp`. Here are the key methods you should use:

### 1. Initialization (`Start`)
Use the `Start()` method for any setup that needs to happen once when the application begins (e.g., loading textures, initializing game objects).
```cpp
void RendererWindow::Start() {
    // Your initialization code here
}
```

### 2. Update Logic (`Timer`)
The `Timer()` method is called every frame. Use this for physics, movement, and logic updates. You can use `deltaTime` for frame-independent movement.
```cpp
void RendererWindow::Timer() {
    // Your update logic here (e.g., position += velocity * deltaTime)
}
```

### 3. Rendering (`Draw`)
The `Draw()` method is where all your OpenGL drawing commands should go. It is called every time the window needs to be redrawn.
```cpp
void RendererWindow::Draw() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    // Your OpenGL drawing code here
    glutSwapBuffers();
}
```

### 4. Input Handling
Handle user input in the following methods:
- `MouseClick`: For mouse button presses and releases.
- `MouseMotion`: For mouse movement while a button is held.
- `MousePassiveMotion`: For mouse movement without buttons held.
- `MouseScrollwheel`: For scroll wheel events.

## Getting Started

### Setup
1. Clone the repository.
2. Open `OpenGL-Feeglut-Starter-Pack.sln` in Visual Studio.
3. Ensure the configuration is set to `Debug x86` or `Release x86` and the platform matches the library.
4. Build and Run (F5).
