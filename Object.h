#pragma once
#include <SDL.h>

class Object
{
public:
	Object();

public:
	virtual void draw(SDL_Renderer* renderer);
	virtual void update();
};

