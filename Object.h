#pragma once
#include <SDL.h>
#include <iostream>
#include <functional>

class Object
{
public:
	Object();
	virtual ~Object() = default;

	virtual void setSurface(SDL_Surface* new_surface);
	virtual void draw(SDL_Renderer* renderer) { std::cout << "Object::draw();\n"; };
	virtual void update() {};
protected:

	SDL_Surface* surface = nullptr;
};

