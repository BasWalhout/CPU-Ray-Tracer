#include <SDL.h>
#include "headers/Application.h"


#undef main
int main() {

	Application application = Application();
	application.InitializeWindow();

	application.Loop();

	return 0;
}