#pragma once
#include <vector>
#include <SDL.h>

#include "Figure.h"

constexpr SDL_Color DEFAULT_FILL_COLOR{ 70, 94, 140 };		 //Dark blue
constexpr SDL_Color DEFAULT_OUTLINE_COLOR{ 115, 148, 191 };  //Light blue

class CircleFigure : public Figure
{
public:
	explicit CircleFigure();
	explicit CircleFigure(const SDL_Color& fillColor);
	explicit CircleFigure(const SDL_Color& outlineColor, const SDL_Color& fillColor = DEFAULT_FILL_COLOR);

public:
	virtual void draw(SDL_Renderer* renderer);
	virtual void update() {};

	void setFillColor(SDL_Color& newColor);
	void setOutlineColor(SDL_Color& newColor);

public:
	double radius;
	SDL_Color fillColor = DEFAULT_FILL_COLOR;
	SDL_Color outlineColor = DEFAULT_OUTLINE_COLOR;

private:
	void DrawCircle(SDL_Renderer* renderer);
};

