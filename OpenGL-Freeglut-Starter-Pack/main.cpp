#include "main.h"
#include "Renderer-Window.h"

int main(int argc, char* argv[]) {
	LOG_DEBUG("Starting application...")

	CRendererWindow* main_window = new CRendererWindow(800, 600, "Shalvex Novachrono's OpenGL Window");

	main_window->Init(argc, argv);
	main_window->CleanUp();

	delete main_window;
	return 0;
}