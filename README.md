# OpenGL - FreeGLUT STARTER

## Overview
This project initialises an OpenGL rendering environment using GLUT/FreeGLUT. The `OpenGLRenderer.cpp` file contains the setup and main loop of the renderer. If you want to modify or extend the rendering logic, read below to see where to insert your code.

## Where to Write Your Code

### Rendering Logic
To add your own drawing logic, modify the `Display` function in `OpenGLRenderer.cpp`:
```cpp
void OpenGLRenderer::Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    // Add your rendering code here
    
    glFlush();
    glutSwapBuffers();
}
```

### Updating Logic
If you need to update objects (e.g., animations, movement), modify the `Update` function:
```cpp
void OpenGLRenderer::Update() {
    
    // Add update logic here (e.g., moving objects, handling game logic)
    
    LogIt("FPS: " + to_string(1 / DELTA_TIME));
    Print_Debug_Log();
    glutPostRedisplay();
}
```

### Using Delta Time
A `DELTA_TIME` float variable is available for handling frame time differences. Use it to ensure smooth animations and movement.

### Debug Logging
You can log messages using the `LogIt` function:
```cpp
LogIt("Your message here");
```
To print logs, use:
```cpp
Print_Debug_Log();
```

## Additional Notes
- Modify `glutCreateWindow("Shalvex Novachrono")` if you want to change the window title.
- Adjust `WINDOW_WIDTH` and `WINDOW_HEIGHT` to modify the window size.
- Change `FRAME_RATE` if you want a different frame rate.

## Running the Project
Ensure you have GLUT installed and compile the project using an OpenGL-compatible compiler. Run the executable to start the rendering loop.

---

Now you're ready to customise your OpenGL renderer! 🚀

*This README has been generated using AI. Only this README has been AI-generated; all other code is original.*

