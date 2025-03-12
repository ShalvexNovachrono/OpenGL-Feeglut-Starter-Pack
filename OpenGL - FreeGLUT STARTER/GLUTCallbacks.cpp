#include "GLUTCallbacks.h"
#include "OpenGLRenderer.h"

/// <summary>
/// GLUTCallbacks namespace.
/// this namespace is used to create the GLUTCallbacks class.
/// </summary>
namespace GLUTCallbacks {
	namespace {
		OpenGLRenderer* openGLRenderer = nullptr;
	}

	void Init(OpenGLRenderer* gl) {
		openGLRenderer = gl;
	}

	/// <summary>
	/// DISPLAY function.
	/// This function is used to display the OpenGLRenderer display.
	/// </summary>
	void Display() {
		if (openGLRenderer != nullptr) {
			openGLRenderer->Display();
		}
	}

	/// <summary>
	/// TIMER function.
	/// This function is used to update the OpenGLRenderer update.
	/// </summary>
	/// <param name="preferredRefresh"></param>
	void Timer(int preferredRefresh) {
		if (openGLRenderer != nullptr) {
			openGLRenderer->Update();
			glutTimerFunc(preferredRefresh, GLUTCallbacks::Timer, preferredRefresh);
		}
	}
}