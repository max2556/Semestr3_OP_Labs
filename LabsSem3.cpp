#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

void draw(SDL_Renderer* p_renderer);

int main()
{
	std::cout << "SDL2 Lab#16" << '\n';

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
		std::cout << "SDL_Init Error:" << SDL_GetError() << std::endl;
		return 1;
	}


	SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	draw(ren);
	
	SDL_Delay(2000);
	
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
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