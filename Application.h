#pragma once
#include <SDL.h>
#include <vector>
#include "Object.h"

//Statics goes everywhere with application.
//Было бы странно передавать класс приложения, без состояния самого приложения
#include "Statics.h"

class Application
{
public:
	Application();
	~Application();

	void Init();
	void Start();
	
	const SDL_Window* getWindow() const;
	const SDL_Renderer* getRenderer() const;
	void Append_Object(Object* object);

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

