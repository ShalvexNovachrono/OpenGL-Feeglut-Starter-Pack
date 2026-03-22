#include "Glut-Callbacks.h"
#include "Renderer-Window.h"

namespace GlutCallbacks {
	namespace {
		CRendererWindow* rw_instance = nullptr;
	}


	void Init(CRendererWindow* rw) {
		rw_instance = rw;
	}

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

	void Timer(int preferred_refresh) {
		if (rw_instance != nullptr) {
			rw_instance->Timer();
			glutTimerFunc(preferred_refresh, GlutCallbacks::Timer, preferred_refresh);
		}
	}

	void MouseClick(int button, int state, int x, int y) {
		if (rw_instance != nullptr) {
			rw_instance->MouseClick(button, state, x, y);
		}
		glutPostRedisplay();
	}

	void MouseMotion(int x, int y) {
		if (rw_instance != nullptr) {
			rw_instance->MouseMotion(x, y);
		}
	}

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
