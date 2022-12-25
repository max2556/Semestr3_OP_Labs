#pragma once
#include <vector>
#include <SDL.h>

#include "Figure.h"

class CircleFigure : public Figure
{
public:
	CircleFigure();
	
public:
	virtual void draw(SDL_Renderer* renderer);
	virtual void update();

public:
	double radius;
	SDL_Color fillColor;
	SDL_Color outlineColor;

private:
	void DrawCircle(SDL_Renderer* renderer);
};

