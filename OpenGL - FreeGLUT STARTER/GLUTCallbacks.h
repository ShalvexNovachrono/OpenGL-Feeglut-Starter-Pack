#pragma once
class OpenGLRenderer;

namespace GLUTCallbacks {
	void Init(OpenGLRenderer* gl);
	void Display();
	void Timer(int preferredRefresh);
}