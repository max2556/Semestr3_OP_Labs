#define SDL_MAIN_HANDLED
#include <iostream>
#include "Application.h"

void draw(SDL_Renderer* p_renderer);

int main()
{
	std::cout << "SDL2 Lab#16" << '\n';
	Application app;
	


	SDL_Delay(2000);
}

void draw(SDL_Renderer* p_renderer)
{
	SDL_RenderClear(p_renderer);

	SDL_Rect rect;
	rect.x = 10;
	rect.y = 10;
	rect.w = 200;
	rect.h = 200;

	SDL_SetRenderDrawColor(p_renderer, 190, 80, 120, 255);
	SDL_RenderFillRect(p_renderer, &rect);

	SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);

	SDL_RenderPresent(p_renderer);
}