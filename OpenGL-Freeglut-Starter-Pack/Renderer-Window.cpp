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
	if (assetManager != nullptr) {
		delete assetManager;
		assetManager = nullptr;
	}
}

void CRendererWindow::Start() {
	didTimerGetCalled = true;
	
	assetManager->LoadMeshFromObjAsync("zombie", "./Assets/Porsche_911_GT2.obj");
	assetManager->LoadTexture("shrek", "./Assets/shrek5.jpg", 0, 0);
	
	worldPosition = Vec3(0.0f, -5.0f, -20.0f);
	
	input->AddDeltaInputAction("Vertical", {'W', 'S'});
	input->AddDeltaInputAction("Vertical", {'w', 's'});
	input->AddDeltaInputAction("Vertical", {GLUT_KEY_UP, GLUT_KEY_DOWN});
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
	LOG_DEBUG_R(
		"FPS: " + to_string(fps) + " | Mouse Pos: " + mousePosStr + " | Mouse Delta: " + mousePositionDeltaStr +
		" | \nMouse State: " + mouseStateStr + " | DeltaTime: " + to_string(deltaTime) + " | System DeltaTime: " +
		to_string(systemDeltaTime) + " | Current Frame: " + to_string(currentFrame))
	//-------End-------//
	

	worldRotation += Vec3(0.0f, deltaTime * 100.0f, 0.0f);

	input->BeginFrame();
	assetManager->UploadPendingTextures();
	glutPostRedisplay();
}

void CRendererWindow::Draw() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);

	// ==========================================
	// WORLD SPACE RENDERING (3D)
	// ==========================================
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(worldPosition.x, worldPosition.y, worldPosition.z);
	glRotatef(worldRotation.x, 1, 0, 0);
	glRotatef(worldRotation.y, 0, 1, 0);
	glRotatef(worldRotation.z, 0, 0, 1);

	// Render here
	Mesh* porscheModel = assetManager->GetMesh("zombie");

	if (porscheModel != nullptr) {

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, porscheModel->vertices);
		glNormalPointer(GL_FLOAT, 0, porscheModel->normals);
		glTexCoordPointer(2, GL_FLOAT, 0, porscheModel->texCoords);

		glDrawElements(GL_TRIANGLES, porscheModel->indexCount, GL_UNSIGNED_SHORT, porscheModel->indices);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	}
	
	//

	glPopMatrix();

	// ==========================================
	// SCREEN SPACE RENDERING (2D / UI)
	// ==========================================
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // Save the 3D Projection matrix
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height); // Set up 2D coordinate system (0,0 is bottom-left)

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); // Save the 3D ModelView matrix
	glLoadIdentity(); 

	glDisable(GL_DEPTH_TEST); // UI doesn't need depth testing

	// Render here
	
	CTextureLoader* shrekTex = assetManager->GetTexture("shrek");
	if (shrekTex != nullptr) {
		float uiSize = 150.0f;
		float padding = 20.0f;
 		
		glPushMatrix();
		// Position at bottom-right
		glTranslatef(width - uiSize - padding, padding, 0.0f);
 		
		glBindTexture(GL_TEXTURE_2D, shrekTex->GetID());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(uiSize, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(uiSize, uiSize);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, uiSize);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
	}
	
	//

	glEnable(GL_DEPTH_TEST); // Re-enable depth testing for the next frame

	glPopMatrix(); // Restore 3D ModelView matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); // Restore 3D Projection matrix
	glMatrixMode(GL_MODELVIEW);

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
