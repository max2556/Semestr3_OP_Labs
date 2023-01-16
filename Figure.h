#pragma once
#include "Object.h"

class Figure : public Object
{
public:
	Figure() : Object() {};
	~Figure() {};

public:
	SDL_FPoint currentPosition;
};

