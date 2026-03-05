#include "main.h"
#include "Renderer-Window.h"

int main(int argc, char* argv[]) {
	LOG_DEBUG("Starting application...")
	
	CRendererWindow* mainWindow = new CRendererWindow(800, 600, "Shalvex Novachrono's OpenGL Window");

	mainWindow->Init(argc, argv);
	mainWindow->CleanUp();

	delete mainWindow;
	return 0;
}