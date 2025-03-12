#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <queue>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Vector2D.h"

using namespace std;

class OpenGLRenderer {
public:

	OpenGLRenderer(int argc, char* argv[]);

	~OpenGLRenderer(void);

	/// <summary>
	/// This function displays objects;
	/// </summary>
	void Display();

	/// <summary>
	/// This function does other logic
	/// </summary>
	void Update();

	/// <summary>
	/// This function calculates the delta time.
	/// </summary>
	void DELTA_TIME_FUNC();

	void LogIt(string log = "");

	void Print_Debug_Log();
private:
	Vector2D WORLD_POSITION = Vector2D(0, 0);

	queue<string> LOG;

	float LAST_TIME = 0.0f;
	float CURRENT_TIME = 0.0f;
	float DELTA_TIME = 0.0f;
};

