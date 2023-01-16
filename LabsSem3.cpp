#define SDL_MAIN_HANDLED
#include <iostream>
#include "Application.h"
#include "CircleFigure.h"
#include "Leader.h"

int main()
{
	std::cout << "SDL2 Lab#16" << '\n';
	Application app;

	CircleFigure circle({255,0,0}, {0,255,0});
	Leader circleMover(static_cast<Figure*>(&circle));
	app.Append_Object(static_cast<Object*>(&circleMover));

	app.Start();
}
