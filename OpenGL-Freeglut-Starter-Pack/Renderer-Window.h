#ifndef RendererWindow
#define RendererWindow

#include "Input-Manager.h"
#include "main.h"
#include "Maths.h"

using namespace std;

class CRendererWindow {
public:

	CRendererWindow(const int& width, const int&  height, const string& title);
	~CRendererWindow() = default;

	void Init(int argc, char* argv[]);

	void CleanUp();

	void Start();

	void Timer();

	void Draw() const;

	void MouseClick(int button, int state, int x, int y) const;

	void MouseMotion(int x, int y) const;

	void MousePassiveMotion(int x, int y) const;

	void MouseScrollWheel(int button, int scrollDirection, int x, int y) const;
	
	void Keyboard(unsigned char key, int x, int y) const;
	
	void KeyboardSpecial(int key, int x, int y) const;

	void KeyboardUp(unsigned char key, int x, int y) const;

	void KeyboardSpecialUp(int key, int x, int y) const;

	float GetDeltaTime() const { return deltaTime; }

	float GetSystemDeltaTime() const { return systemDeltaTime; }

	float GetTimeScale() const { return timeScale; }

	void SetTimeScale(float scale) { timeScale = scale; }

	void ReshapeWindow(const int& width, const int& height);

	int GetFps() const { return fps; }

	float GetFov() const { return fov; }

	void SetFov(float new_fov);

	void UpdateWindowDetails() const;

	Vec2 GetWindowSize() const { return { static_cast<float>(width), static_cast<float>(height) }; }

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
	const float minimumFov = 1.0f;
	const float maximumFov = 110.0f;
	const float frameRate = 145;
	const int frameTime = static_cast<int>(1000.0f / frameRate);

	Vec3 worldPosition = Vec3(0, 0, 0);
	Vec3 worldRotation = Vec3(0, 0, 0);
	Vec4 clearColor = Vec4(0.2f, 0.3f, 0.3f, 1.0f);

	CInputManager* input = nullptr;	
	
	bool didTimerGetCalled = false;
};

#endif
