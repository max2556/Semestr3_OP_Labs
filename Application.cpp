#include "Application.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>


Application::Application()
{
	Init();
}

Application::~Application()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Application::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error:" << SDL_GetError() << std::endl;
		throw std::logic_error("Init Error");
		return;
	}

	Init_window();
	Init_renderer();
	
	//Init deltatime
	Statics::getInstance()->calculateDeltaTime();
	//Init isRunning
	Statics::getInstance()->isRunning = true;
}

void Application::Init_window()
{
	window = SDL_CreateWindow("Lab#16", 100, 100, 1024, 720, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		throw std::logic_error("Init_window Error");
		return;
	}
}

void Application::Init_renderer()
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		throw std::logic_error("Init_renderer Error");
		return;
	}
}

void Application::try_get_screen()
{
	if (SDL_GetDesktopDisplayMode(0, &settings.screenData))
	{
		std::cout << "Cannot get desctop screen data! \n" << SDL_GetError() << std::endl;
	}
}

SDL_Window* Application::getWindow() const
{
	return window;
}

SDL_Renderer* Application::getRenderer() const
{
	return renderer;
}

void Application::main_loop()
{
	Statics* stats = Statics::getInstance();

	SDL_Rect rect{}; rect.w = 30; rect.h = 40;
	while (stats->isRunning)
	{
		event_handling();
		update_all();
		draw_all();

		SDL_RenderPresent(renderer);
		SDL_Delay(0);
	}
}

void Application::update_all()
{
	for (Object* obj : objects)
	{
		obj->update();
	}
}

void Application::draw_all()
{
	SDL_SetRenderDrawColor(renderer, 127, 60, 180, 128);
	SDL_RenderClear(renderer);
	for (Object* obj : objects)
	{
		obj->draw(renderer);
	}
}

void Application::event_handling()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) > 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			Statics::getInstance()->isRunning = false;
			break;
			
		default:
			//std::cout << "Event type: " << e.type << '\n';
			break;
		}
	}
}

void Application::Append_Object(Object& object)
{
	object.setSurface(SDL_GetWindowSurface(window));
	objects.push_back(&object);
}

void Application::Start()
{
	main_loop();
}