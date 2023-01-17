#pragma once
#include <vector>
#include <SDL.h>

#include "Figure.h"

class CircleFigure : public Figure
{
public:
	explicit CircleFigure();
	explicit CircleFigure(const SDL_Color& fillColor);
	explicit CircleFigure(const SDL_Color& outlineColor, const SDL_Color& fillColor = DEFAULT_FILL_COLOR);

public:
	virtual void draw(SDL_Renderer* renderer) override;
	virtual void update() override {};
	void setRadius(double radius);

public:
	double radius;

private:
	void DrawCircle(SDL_Renderer* renderer);
};

