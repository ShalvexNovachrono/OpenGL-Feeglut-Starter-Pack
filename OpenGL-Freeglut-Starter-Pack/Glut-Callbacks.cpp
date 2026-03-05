#include "Glut-Callbacks.h"
#include "Renderer-Window.h"

/// <summary>
/// GLUTCallbacks namespace.
/// this namespace is used to create the GLUTCallbacks class.
/// </summary>
namespace GlutCallbacks {
	namespace {
		CRendererWindow* rw_instance = nullptr;
	}


	void Init(CRendererWindow* rw) {
		rw_instance = rw;
	}

	/// <summary>
	/// DISPLAY function.
	/// This function is used to display the OpenGLRenderer display.
	/// </summary>
	void Display() {
		if (rw_instance != nullptr) {
			rw_instance->Draw();
		}
	}

	void ReshapeWindow(int width, int height) {
		if (rw_instance != nullptr) {
			rw_instance->ReshapeWindow(width, height);
		}
	}

	/// <summary>
	/// This will constantly call the timer function of the r_window at a preferred refresh rate.
	/// </summary>
	/// <param name="preferred_refresh"></param>
	void Timer(int preferred_refresh) {
		if (rw_instance != nullptr) {
			rw_instance->Timer();
			glutTimerFunc(preferred_refresh, GlutCallbacks::Timer, preferred_refresh);
		}
	}



	/// <summary>
	/// Mouse click function callback.
	/// </summary>
	/// <param name="Button">The mouse button involved (e.g., GLUT_LEFT_BUTTON).</param>
	/// <param name="State">The state of the button (GLUT_DOWN or GLUT_UP).</param>
	/// <param name="X">The window-relative x-coordinate of the mouse.</param>
	/// <param name="Y">The window-relative y-coordinate of the mouse.</param>
	void MouseClick(int button, int state, int x, int y) {
		if (rw_instance != nullptr) {
			rw_instance->MouseClick(button, state, x, y);
		}
		glutPostRedisplay();
	}

	/// <summary>
	/// Mouse motion function callback.
	/// </summary>
	/// <param name="x">The current window-relative x-coordinate of the mouse cursor.</param>
	/// <param name="y">The current window-relative y-coordinate of the mouse cursor.</param>
	void MouseMotion(int x, int y) {
		if (rw_instance != nullptr) {
			rw_instance->MouseMotion(x, y);
		}
	}


	/// <summary>
	/// Mouse passive motion function callback.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void MousePassiveMotion(int x, int y) {
		if (rw_instance != nullptr) {
			rw_instance->MousePassiveMotion(x, y);
		}
	}

	void MouseScrollWheel(int button, int scrollDirection, int x, int y) {
		if (rw_instance != nullptr) {
			rw_instance->MouseScrollWheel(button, scrollDirection, x, y);
		}
	}

	void Keyboard(unsigned char key, int x, int y) {
		if (rw_instance != nullptr) {
			rw_instance->Keyboard(key, x, y);
		}
	}
	
	void KeyboardSpecial(int key, int x, int y) {
		if (rw_instance != nullptr) {
			rw_instance->KeyboardSpecial(key, x, y);
		}
	}

	void KeyboardUp(unsigned char key, int x, int y) {
		if (rw_instance != nullptr) {
			rw_instance->KeyboardUp(key, x, y);
		}
	}

	void KeyboardSpecialUp(int key, int x, int y) {
		if (rw_instance != nullptr) {
			rw_instance->KeyboardSpecialUp(key, x, y);
		}
	}
}
