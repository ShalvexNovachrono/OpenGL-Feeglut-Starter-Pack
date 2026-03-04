#include "Renderer-Window.h"
#include "Glut-Callbacks.h"

RendererWindow::RendererWindow(const int& width, const int&  height, const string& title) {
    this->width = width;
    this->height = height;
    this->title = title;
}

void RendererWindow::Init(int argc, char* argv[]) {

	GlutCallbacks::Init(this);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// Setting up window size and window name
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());

	// Setting up the glut callbacks
	glutDisplayFunc(GlutCallbacks::Display);
	glutReshapeFunc(GlutCallbacks::ReshapeWindow);
	glutMouseFunc(GlutCallbacks::MouseClick);
	glutMotionFunc(GlutCallbacks::MouseMotion);
	glutPassiveMotionFunc(GlutCallbacks::MousePassiveMotion);
	glutMouseWheelFunc(GlutCallbacks::MouseScrollWheel);
	glutKeyboardFunc(GlutCallbacks::Keyboard);
	glutSpecialFunc(GlutCallbacks::KeyboardSpecial);
	glutTimerFunc(frameTime, GlutCallbacks::Timer, frameTime);

	// Switching camera to projection mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);
	gluPerspective(fov, static_cast<float>(width) / static_cast<float>(height), 0.1, 1800);
	glMatrixMode(GL_MODELVIEW);
	
	
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	glutMainLoop();

}

void RendererWindow::CleanUp() {
}

void RendererWindow::Start() {
	didTimerGetCalled = true;

	
	
	
}

void RendererWindow::Timer() {
	currentFrame = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));              // seconds
	systemDeltaTime = (currentFrame - lastFrame) / 1000.0f;
	if (systemDeltaTime <= 0.0f) systemDeltaTime = 1e-6f;
	deltaTime = timeScale * systemDeltaTime;
	lastFrame = currentFrame;
	fps = static_cast<int>(1.0f / systemDeltaTime);

	//-------Debug-Info-------//
	LOG_DEBUG_R("FPS: " + to_string(fps) + " | Delta Time: " + to_string(deltaTime) + " | System Delta Time: " + to_string(systemDeltaTime))
	//-------End-------//

	
	glutPostRedisplay();
}

void RendererWindow::Draw() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(worldPosition.x, worldPosition.y, worldPosition.z);
	glRotatef(worldRotation.x, 1, 0, 0);
	glRotatef(worldRotation.y, 0, 1, 0);
	glRotatef(worldRotation.z, 0, 0, 1);



	glPopMatrix();
	glutSwapBuffers();
}

void RendererWindow::MouseClick(int button, int state, int x, int y) const {
	
}

void RendererWindow::MouseMotion(int x, int y) const {
	
}

void RendererWindow::MousePassiveMotion(int x, int y) const {
	
}

void RendererWindow::MouseScrollWheel(int button, int scrollDirection, int x, int y) const {
	
}

void RendererWindow::Keyboard(unsigned char key, int x, int y) const {

}

void RendererWindow::KeyboardSpecial(int key, int x, int y) const {
	if (key == GLUT_KEY_F1) 
	{
		LOG_DEBUG("F1 PRESSED")
	}
}

void RendererWindow::ReshapeWindow(const int& width, const int&  height) {
	this->width = width;
	this->height = height;
	glutReshapeWindow(width, height);
	UpdateWindowDetails();
}

void RendererWindow::SetFov(float new_fov) {
	if (new_fov < minimumFov) return;
	if (new_fov > maximumFov) return;
	fov = new_fov;
	UpdateWindowDetails();
}

void RendererWindow::UpdateWindowDetails() const {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(fov, static_cast<float>(width) / static_cast<float>(height), 0.1, 1800);
	glMatrixMode(GL_MODELVIEW);
}