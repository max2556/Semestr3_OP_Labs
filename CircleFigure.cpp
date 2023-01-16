#include <iostream>

#include "CircleFigure.h"
#include "SDL_gfxPrimitives.h"

CircleFigure::CircleFigure() :
	Figure()
{
	surface = SDL_CreateRGBSurface(0, 2 * radius, 2 * radius, 32, 0, 0, 0, 0);
	if (!surface)
	{
		std::cout << "Error while creating surface:" << SDL_GetError() << std::endl;
		return;
	}
}

CircleFigure::CircleFigure(const SDL_Color& fillColor) :
	CircleFigure()
{
	this->fillColor = fillColor;
}

CircleFigure::CircleFigure(const SDL_Color& outlineColor, const SDL_Color& fillColor) :
	CircleFigure()
{
	this->outlineColor = outlineColor;
	this->fillColor = fillColor;
}

void CircleFigure::draw(SDL_Renderer* renderer)
{
	Figure::draw(renderer);

    DrawCircle(renderer);
}

void CircleFigure::DrawCircle(SDL_Renderer* renderer)
{
	filledCircleRGBA(
		surface,
		currentPosition.x, currentPosition.y,
		radius,
		fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	circleRGBA(
		surface,
		currentPosition.x, currentPosition.y,
		radius,
		outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
}

void CircleFigure::setFillColor(SDL_Color& newColor)
{
	fillColor = newColor;
}

void CircleFigure::setOutlineColor(SDL_Color& newColor)
{
	outlineColor = newColor;
}



