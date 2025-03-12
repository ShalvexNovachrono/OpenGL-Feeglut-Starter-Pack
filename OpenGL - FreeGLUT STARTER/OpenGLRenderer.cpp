#include "OpenGLRenderer.h"
#include "GLUTCallbacks.h"
#include "Vector2D.h"

#define FRAME_RATE 144
#define FRAME_TIME 1000 / FRAME_RATE

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define CAMERA_SPEED 0.1f

OpenGLRenderer::OpenGLRenderer(int argc, char* argv[]) {

	GLUTCallbacks::Init(this); // Initialise the GLUTCallbacks with the current instance of the OpenGLRenderer.

	glutInit(&argc, argv); // Initialise GLUT with the arguments passed to the main function.
	glutInitDisplayMode(GLUT_DOUBLE); // Set the display mode to double buffering.

	glEnable(GL_CULL_FACE); // Enable culling of faces.
	glCullFace(GL_BACK); 

	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Set the window size.
	glutCreateWindow("Shalvex Novachrono"); // Create the window with the title 

	glutDisplayFunc(GLUTCallbacks::Display); // Set the display function to the Display function in the GLUTCallbacks namespace.
	glutTimerFunc(FRAME_TIME, GLUTCallbacks::Timer, FRAME_TIME); // Set the timer function to the Timer function in the GLUTCallbacks namespace.

	glutMainLoop(); // Start the main loop.
}


void OpenGLRenderer::Display() {


	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glFlush();
	glutSwapBuffers();


}

void OpenGLRenderer::Update() {
	DELTA_TIME_FUNC();

	LogIt("FPS: " + to_string(1 / DELTA_TIME));
	Print_Debug_Log();
	glutPostRedisplay();
}

void OpenGLRenderer::DELTA_TIME_FUNC() {
	CURRENT_TIME = (float)glutGet(GLUT_ELAPSED_TIME);
	DELTA_TIME = (CURRENT_TIME - LAST_TIME) / 1000.0f;
	LAST_TIME = CURRENT_TIME;
}

void OpenGLRenderer::LogIt(string log) {
	if (LOG.size() > 99) {
		LOG.pop();
	}
	LOG.push(log);
}

void OpenGLRenderer::Print_Debug_Log() {
	cout << "\r";
	for (int i = 0; i <= LOG.size(); i++) {
		cout << LOG.front() << "\n";
		LOG.pop();
	}
	cout << flush;
}


OpenGLRenderer::~OpenGLRenderer() {

}
