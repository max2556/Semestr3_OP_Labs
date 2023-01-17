#include <iostream>
#include "CircleFigure.h"

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius);

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

void CircleFigure::setRadius(double radius)
{
    this->radius = radius;
}

void CircleFigure::draw(SDL_Renderer* renderer)
{
	Figure::draw(renderer);

    DrawCircle(renderer);
}

void CircleFigure::DrawCircle(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillCircle(renderer, currentPosition.x, currentPosition.y, radius);
}

///Взято из интернета. Интересным методом рисует круг
int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
            x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
            x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
            x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
            x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}


