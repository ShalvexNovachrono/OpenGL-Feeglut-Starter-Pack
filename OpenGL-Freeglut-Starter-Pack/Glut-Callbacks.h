#pragma once
class CRendererWindow;

namespace GlutCallbacks {
	void Init(CRendererWindow* rw);
	void Display();
	void ReshapeWindow(int width, int height);
	void Timer(int preferred_refresh);
	void MouseClick(int button, int state, int x, int y);
	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);
	void MouseScrollWheel(int button, int scrollDirection, int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardSpecial(int key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void KeyboardSpecialUp(int key, int x, int y);
}