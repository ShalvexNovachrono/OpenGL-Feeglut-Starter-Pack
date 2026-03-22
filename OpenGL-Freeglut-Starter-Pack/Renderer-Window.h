#ifndef RendererWindow
#define RendererWindow

#include "Asset-Manager.h"
#include "main.h"
#include "Input-Manager.h"
#include "Maths.h"

class CRendererWindow {
public:
	/// <summary>
	/// Constructs a CRendererWindow object.
	/// </summary>
	/// <param name="width">The width of the window.</param>
	/// <param name="height">The height of the window.</param>
	/// <param name="title">The title of the window.</param>
	CRendererWindow(const int& width, const int&  height, const string& title);

	/// <summary>
	/// Destructor for CRendererWindow.
	/// </summary>
	~CRendererWindow() = default;

	/// <summary>
	/// Initializes the OpenGL context and FreeGLUT window.
	/// </summary>
	/// <param name="argc">Argument count from main.</param>
	/// <param name="argv">Argument vector from main.</param>
	void Init(int argc, char* argv[]);

	/// <summary>
	/// Cleans up resources used by the renderer window.
	/// </summary>
	void CleanUp();

	/// <summary>
	/// Starts the main FreeGLUT event loop.
	/// </summary>
	void Start();

	/// <summary>
	/// Timer callback function for FreeGLUT. Handles frame rate and delta time calculation.
	/// </summary>
	void Timer();

	/// <summary>
	/// Drawing callback function for FreeGLUT. Renders the scene.
	/// </summary>
	void Draw() const;

	/// <summary>
	/// Mouse click callback function for FreeGLUT.
	/// </summary>
	/// <param name="button">The mouse button that was clicked.</param>
	/// <param name="state">The state of the mouse button (GLUT_DOWN or GLUT_UP).</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void MouseClick(int button, int state, int x, int y) const;

	/// <summary>
	/// Mouse motion callback function for FreeGLUT (when a button is pressed).
	/// </summary>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void MouseMotion(int x, int y) const;

	/// <summary>
	/// Mouse passive motion callback function for FreeGLUT (when no button is pressed).
	/// </summary>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void MousePassiveMotion(int x, int y) const;

	/// <summary>
	/// Mouse scroll wheel callback function for FreeGLUT.
	/// </summary>
	/// <param name="button">The scroll direction (GLUT_SCROLL_UP or GLUT_SCROLL_DOWN).</param>
	/// <param name="scrollDirection">The scroll direction (1 for up, -1 for down).</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void MouseScrollWheel(int button, int scrollDirection, int x, int y) const;
	
	/// <summary>
	/// Keyboard key press callback function for FreeGLUT.
	/// </summary>
	/// <param name="key">The ASCII value of the pressed key.</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void Keyboard(unsigned char key, int x, int y) const;
	
	/// <summary>
	/// Special keyboard key press callback function for FreeGLUT (e.g., F1, arrow keys).
	/// </summary>
	/// <param name="key">The FreeGLUT special key code.</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void KeyboardSpecial(int key, int x, int y) const;

	/// <summary>
	/// Keyboard key release callback function for FreeGLUT.
	/// </summary>
	/// <param name="key">The ASCII value of the released key.</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void KeyboardUp(unsigned char key, int x, int y) const;

	/// <summary>
	/// Special keyboard key release callback function for FreeGLUT.
	/// </summary>
	/// <param name="key">The FreeGLUT special key code.</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void KeyboardSpecialUp(int key, int x, int y) const;

	/// <summary>
	/// Gets the delta time (time elapsed since the last frame, scaled by timeScale).
	/// </summary>
	/// <returns>The scaled delta time.</returns>
	float GetDeltaTime() const { return deltaTime; }

	/// <summary>
	/// Gets the system delta time (raw time elapsed since the last frame).
	/// </summary>
	/// <returns>The raw system delta time.</returns>
	float GetSystemDeltaTime() const { return systemDeltaTime; }

	/// <summary>
	/// Gets the current time scale.
	/// </summary>
	/// <returns>The time scale value.</returns>
	float GetTimeScale() const { return timeScale; }

	/// <summary>
	/// Sets the time scale for delta time calculations.
	/// </summary>
	/// <param name="scale">The new time scale value.</param>
	void SetTimeScale(float scale) { timeScale = scale; }

	/// <summary>
	/// Reshapes the window to the specified dimensions.
	/// </summary>
	/// <param name="width">The new width of the window.</param>
	/// <param name="height">The new height of the window.</param>
	void ReshapeWindow(const int& width, const int& height);

	/// <summary>
	/// Gets the current frames per second (FPS).
	/// </summary>
	/// <returns>The current FPS.</returns>
	int GetFps() const { return fps; }

	/// <summary>
	/// Gets the current field of view (FOV).
	/// </summary>
	/// <returns>The current FOV.</returns>
	float GetFov() const { return fov; }

	/// <summary>
	/// Sets the field of view (FOV), clamping it between minimum and maximum values.
	/// </summary>
	/// <param name="new_fov">The new FOV value.</param>
	void SetFov(float new_fov);

	/// <summary>
	/// Updates the window title with current details like FPS.
	/// </summary>
	void UpdateWindowDetails() const;

	/// <summary>
	/// Gets the current size of the window.
	/// </summary>
	/// <returns>A Vec2 containing the width and height of the window.</returns>
	Vec2 GetWindowSize() const { return { static_cast<float>(width), static_cast<float>(height) }; }

	/// <summary>
	/// Gets the current position of the window on the screen.
	/// </summary>
	/// <returns>A Vec2 containing the x and y coordinates of the window's top-left corner.</returns>
	static Vec2 GetWindowPosition() { return { static_cast<float>(glutGet(GLUT_WINDOW_X)), static_cast<float>(glutGet(GLUT_WINDOW_Y))}; }
private:
	int width = 100, height = 100;
	string title;

	float deltaTime = 0.0f;
	float systemDeltaTime = 0.0f;
	float lastFrame = 0.0f;
	float timeScale = 1.0f;
	float currentFrame = 0.0f;
	int fps = 0;

	float fov = 45.0f;
	float minimumFov = 1.0f;
	float maximumFov = 110.0f;
	float frameRate = 145;
	int frameTime = static_cast<int>(1000.0f / frameRate);

	Vec3 worldPosition = Vec3(0, 0, 0);
	Vec3 worldRotation = Vec3(0, 0, 0);
	Vec4 clearColor = Vec4(0.2f, 0.3f, 0.3f, 1.0f);

	CInputManager* input = nullptr;	
	CAssetManager* assetManager = nullptr;
	
	bool didTimerGetCalled = false;
};

#endif
