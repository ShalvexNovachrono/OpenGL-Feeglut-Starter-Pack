#pragma once
class CRendererWindow;

namespace GlutCallbacks {
	/// <summary>
	/// Initializes the callback system with a CRendererWindow instance.
	/// </summary>
	/// <param name="rw">A pointer to the CRendererWindow instance to handle events.</param>
	void Init(CRendererWindow* rw);

	/// <summary>
	/// Display callback function for FreeGLUT.
	/// This function is used to display the OpenGLRenderer content.
	/// </summary>
	void Display();

	/// <summary>
	/// Reshape callback function for FreeGLUT.
	/// Called when the window is resized.
	/// </summary>
	/// <param name="width">The new width of the window.</param>
	/// <param name="height">The new height of the window.</param>
	void ReshapeWindow(int width, int height);

	/// <summary>
	/// Timer callback function for FreeGLUT.
	/// This function is called periodically to update the renderer window.
	/// </summary>
	/// <param name="preferred_refresh">The preferred refresh rate in milliseconds.</param>
	void Timer(int preferred_refresh);

	/// <summary>
	/// Mouse click callback function for FreeGLUT.
	/// </summary>
	/// <param name="button">The mouse button involved (e.g., GLUT_LEFT_BUTTON).</param>
	/// <param name="state">The state of the button (GLUT_DOWN or GLUT_UP).</param>
	/// <param name="x">The window-relative x-coordinate of the mouse.</param>
	/// <param name="y">The window-relative y-coordinate of the mouse.</param>
	void MouseClick(int button, int state, int x, int y);

	/// <summary>
	/// Mouse motion callback function for FreeGLUT (when a button is pressed).
	/// </summary>
	/// <param name="x">The current window-relative x-coordinate of the mouse cursor.</param>
	/// <param name="y">The current window-relative y-coordinate of the mouse cursor.</param>
	void MouseMotion(int x, int y);

	/// <summary>
	/// Mouse passive motion callback function for FreeGLUT (when no button is pressed).
	/// </summary>
	/// <param name="x">The current window-relative x-coordinate of the mouse cursor.</param>
	/// <param name="y">The current window-relative y-coordinate of the mouse cursor.</param>
	void MousePassiveMotion(int x, int y);

	/// <summary>
	/// Mouse scroll wheel callback function for FreeGLUT.
	/// </summary>
	/// <param name="button">The scroll direction (GLUT_SCROLL_UP or GLUT_SCROLL_DOWN).</param>
	/// <param name="scrollDirection">The scroll direction (1 for up, -1 for down).</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void MouseScrollWheel(int button, int scrollDirection, int x, int y);

	/// <summary>
	/// Keyboard key press callback function for FreeGLUT.
	/// </summary>
	/// <param name="key">The ASCII value of the pressed key.</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void Keyboard(unsigned char key, int x, int y);

	/// <summary>
	/// Special keyboard key press callback function for FreeGLUT (e.g., F1, arrow keys).
	/// </summary>
	/// <param name="key">The FreeGLUT special key code.</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void KeyboardSpecial(int key, int x, int y);

	/// <summary>
	/// Keyboard key release callback function for FreeGLUT.
	/// </summary>
	/// <param name="key">The ASCII value of the released key.</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void KeyboardUp(unsigned char key, int x, int y);

	/// <summary>
	/// Special keyboard key release callback function for FreeGLUT.
	/// </summary>
	/// <param name="key">The FreeGLUT special key code.</param>
	/// <param name="x">The x-coordinate of the mouse pointer.</param>
	/// <param name="y">The y-coordinate of the mouse pointer.</param>
	void KeyboardSpecialUp(int key, int x, int y);
}