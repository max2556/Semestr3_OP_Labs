#pragma once
#include <SDL.h>

static class Statics
{
public:
	double deltaTime;
	bool isRunning;

public:
	static Statics* getInstance();

	double getDeltaTime();
	void calculateDeltaTime();

private:
	Uint64 NOW = 0;
	Uint64 LAST = 0;

private:
	static Statics* instance;
	Statics() = default;
	Statics(Statics const&) = delete;
	void operator=(Statics const&) = delete;
};

