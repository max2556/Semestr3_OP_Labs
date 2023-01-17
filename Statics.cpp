#include "Statics.h"

Statics* Statics::instance = nullptr;

double Statics::getDeltaTime()
{
	return deltaTime;
}

void Statics::calculateDeltaTime() 
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();

	deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	deltaTime = 0.001;
}

Statics* Statics::getInstance()
{
	if (!instance)
		instance = new Statics();

	return instance;
}