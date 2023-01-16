#pragma once
#include <SDL.h>

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

public:
	virtual void draw(SDL_Renderer* renderer) {};
	virtual void update() {};
	virtual void setSurface(SDL_Surface* new_surface);

protected:
	SDL_Surface* surface = nullptr;
};

