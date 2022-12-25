#pragma once
#include <SDL.h>

SDL_FPoint operator+(SDL_FPoint first, SDL_FPoint second)
{
	SDL_FPoint result;
	result.x = first.x - second.x;
	result.y = first.y - second.y;
	return result;
}

inline SDL_FPoint operator-(SDL_FPoint point)
{
	SDL_FPoint result;
	result.x = -point.x;
	result.y = -point.y;
	return result;
}

inline SDL_FPoint operator-(SDL_FPoint first, SDL_FPoint second)
{
	SDL_FPoint result = first + (-second);
	return result;
}

inline SDL_FPoint operator*(SDL_FPoint vector, double modifier)
{
	SDL_FPoint result;
	result.x = vector.x * modifier;
	result.y = vector.y * modifier;
	return result;
}


inline void operator+=(SDL_FPoint target, SDL_FPoint modifier)
{
	target = target + modifier;
}

inline void operator-=(SDL_FPoint target, SDL_FPoint modifier)
{
	target = target - modifier;
}