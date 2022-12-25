#pragma once
#include "Object.h"

class Figure : public Object
{
public:
	Figure();

public:
	SDL_FPoint currentPosition;

protected:
	SDL_Surface* surface = nullptr;
};

