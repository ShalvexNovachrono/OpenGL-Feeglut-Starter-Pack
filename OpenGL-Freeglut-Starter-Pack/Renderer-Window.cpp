#include "Renderer-Window.h"
#include "Glut-Callbacks.h"

CRendererWindow::CRendererWindow(const int& width, const int&  height, const string& title) {
    this->width = width;
    this->height = height;
    this->title = title;
}

void CRendererWindow::Init(int argc, char* argv[]) {

	#pragma region Setup Manager
	input        = new CInputManager(deltaTime);
	assetManager = new CAssetManager();
	#pragma endregion
	
	
	
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
	glutKeyboardUpFunc(GlutCallbacks::KeyboardUp);
	glutSpecialUpFunc(GlutCallbacks::KeyboardSpecialUp);
	glutTimerFunc(frameTime, GlutCallbacks::Timer, frameTime);

	// Switching camera to projection mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);
	gluPerspective(fov, static_cast<float>(width) / static_cast<float>(height), 0.1, 1800);
	glMatrixMode(GL_MODELVIEW);
	
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	glutMainLoop();

}

void CRendererWindow::CleanUp() {
	if (input != nullptr) {
		delete input;
		input = nullptr;
	}
}

void CRendererWindow::Start() {
	didTimerGetCalled = true;
}

void CRendererWindow::Timer() {
	currentFrame = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));              // seconds
	systemDeltaTime = (currentFrame - lastFrame) / 1000.0f;
	if (systemDeltaTime <= 0.0f) systemDeltaTime = 1e-6f;
	deltaTime = timeScale * systemDeltaTime;
	lastFrame = currentFrame;
	fps = static_cast<int>(1.0f / systemDeltaTime);
	
	if (!didTimerGetCalled) Start();

	//-------Debug-Info-------//
	string mousePosStr = input->GetMousePosition().tostr();
	string mousePositionDeltaStr = input->GetMouseDelta().tostr();
	string mouseStateStr = input->GetMouseMovementStateString();
	LOG_DEBUG_R("FPS: " + to_string(fps) + " | Mouse Pos: " + mousePosStr + " | Mouse Delta: " + mousePositionDeltaStr + " | \nMouse State: " + mouseStateStr + " | DeltaTime: " + to_string(deltaTime) + " | System DeltaTime: " + to_string(systemDeltaTime) + " | Current Frame: " + to_string(currentFrame))
	//-------End-------//

	
	
	

	
	
	input->BeginFrame();
	glutPostRedisplay();
}

void CRendererWindow::Draw() const {
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

void CRendererWindow::MouseClick(int button, int state, int x, int y) const {
	if (input != nullptr) {
		input->SetMouseButtonState(button, state == GLUT_DOWN, Vec2(static_cast<float>(x), static_cast<float>(y)), MouseMovementState::MouseClick);
	}
}

void CRendererWindow::MouseMotion(int x, int y) const {
	if (input != nullptr) {
		input->SetMousePosition(Vec2(static_cast<float>(x), static_cast<float>(y)), MouseMovementState::MouseMotion);
	}
}

void CRendererWindow::MousePassiveMotion(int x, int y) const {
	if (input != nullptr) {
		input->SetMousePosition(Vec2(static_cast<float>(x), static_cast<float>(y)), MouseMovementState::MousePassiveMotion);
	}
}

void CRendererWindow::MouseScrollWheel(int button, int scrollDirection, int x, int y) const {
	if (input != nullptr) {
		input->AddMouseWheelDelta(scrollDirection, Vec2(static_cast<float>(x), static_cast<float>(y)));
	}
}

void CRendererWindow::Keyboard(unsigned char key, int x, int y) const {
	if (input != nullptr) {
		input->SetKeyState(key, true, Vec2(static_cast<float>(x), static_cast<float>(y)), MouseMovementState::KeyboardPress);
	}
}

void CRendererWindow::KeyboardSpecial(int key, int x, int y) const {
	if (input != nullptr) {
		input->SetKeyState(key, true, Vec2(static_cast<float>(x), static_cast<float>(y)), MouseMovementState::KeyboardPress);
	}
}

void CRendererWindow::KeyboardUp(unsigned char key, int x, int y) const {
	if (input != nullptr) {
		input->SetKeyState(key, false, Vec2(static_cast<float>(x), static_cast<float>(y)), MouseMovementState::KeyboardPress);
	}
}

void CRendererWindow::KeyboardSpecialUp(int key, int x, int y) const {
	if (input != nullptr) {
		input->SetKeyState(key, false, Vec2(static_cast<float>(x), static_cast<float>(y)), MouseMovementState::KeyboardPress);
	}
}

void CRendererWindow::ReshapeWindow(const int& newWidth, const int&  newHeight) {
	width = newWidth;
	height = newHeight;
	glutReshapeWindow(width, height);
	UpdateWindowDetails();
}

void CRendererWindow::SetFov(float new_fov) {
	if (new_fov < minimumFov) return;
	if (new_fov > maximumFov) return;
	fov = new_fov;
	UpdateWindowDetails();
}

void CRendererWindow::UpdateWindowDetails() const {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(fov, static_cast<float>(width) / static_cast<float>(height), 0.1, 1800);
	glMatrixMode(GL_MODELVIEW);
}
