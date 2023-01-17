///
/// Движение закрашенного круга по треугольному контуру 
/// с изменением цвета при изменении направления движения.
///

#define SDL_MAIN_HANDLED
#include <iostream>
#include "Application.h"
#include "CircleFigure.h"
#include "Leader.h"

int main()
{
	int radius = 0;
	std::cout << "SDL2 Lab#16" << '\n';
	std::cout << "Circle Radius: ";
	std::cin >> radius;

	std::vector<SDL_FPoint> triangle = { {500,200}, {700,500}, {300,500} };
	
	Application app;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	CircleFigure circle; //Объект круга
	circle.setRadius(radius);

	Leader circleMover(circle, triangle); //Объект, который будет двигать круг по траектории
	circleMover.setSpeed(10);

	app.Append_Object(circleMover);

	app.Start();
}
