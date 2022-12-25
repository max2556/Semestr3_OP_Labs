#pragma once
#include <SDL.h>
#include <vector>
#include "Object.h"

class Application
{
public:
	Application();
	~Application();

	void Init();
	

public:
	const SDL_Window* getWindow() const;
	const SDL_Renderer* getRenderer() const;

public:
	static struct Statics
	{
	private:
		static Uint64 NOW;
		static Uint64 LAST;
	public:
		static double deltaTime;
		static bool isRunning;

	public:
		static double getDeltaTime()
		{
			return deltaTime;
		}
		static void calculateDeltaTime()
		{
			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();

			deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		}
	};

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

