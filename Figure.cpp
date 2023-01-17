#include "Figure.h"

Figure::Figure() : Object() {};

void Figure::setPosition(float x, float y)
{
	currentPosition.x = x;
	currentPosition.y = y;
}

void Figure::setFillColor(SDL_Color& newColor)
{
	fillColor = newColor;
}

void Figure::setOutlineColor(SDL_Color& newColor)
{
	outlineColor = newColor;
}