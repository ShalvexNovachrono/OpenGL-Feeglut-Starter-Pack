#pragma once
class RendererWindow;

namespace GlutCallbacks {
	void Init(RendererWindow* rw);
	void Display();
	void ReshapeWindow(int width, int height);
	void Timer(int preferred_refresh);
	void MouseClick(int button, int state, int x, int y);
	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);
	void MouseScrollwheel(int button, int scrollDirection, int x, int y);
}