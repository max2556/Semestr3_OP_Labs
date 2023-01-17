#pragma once
#include <SDL.h>
#include <vector>
#include "Object.h"

#include "Statics.h" //ƒоступны везде, так как Statics хранит состо€ни€ приложени€

class Application
{
public:
	Application();
	~Application();

	void Init();
	void Start();
	
	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;
	void Append_Object(Object& object);

private:
	struct Settings
	{
		SDL_DisplayMode screenData;
		SDL_FPoint windowData;
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Settings settings;

	std::vector<Object*> objects;

private:
	void Init_window();
	void Init_renderer();
	void try_get_screen();

	void main_loop();
	void draw_all();
	void update_all();
	void event_handling();
};

