#pragma once
#include <SDL.h>

inline SDL_FPoint operator+(const SDL_FPoint& first, const SDL_FPoint& second)
{
	return {first.x + second.x, first.y + second.y};
}

inline SDL_FPoint operator-(const SDL_FPoint& point)
{
	return {-point.x, -point.y};
}

inline SDL_FPoint operator-(const SDL_FPoint& first, const SDL_FPoint& second)
{
	SDL_FPoint result = first + (-second);
	return result;
}

inline SDL_FPoint operator*(const SDL_FPoint& vector, const float modifier)
{
	return {vector.x * modifier, vector.y * modifier};
}

inline SDL_FPoint& operator+=(SDL_FPoint& target, const SDL_FPoint& modifier)
{
	target = target + modifier;
	return target;
}

inline SDL_FPoint& operator-=(SDL_FPoint& target, const SDL_FPoint& modifier)
{
	target = target - modifier;
	return target;
}

long double modulus(const SDL_FPoint& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

long double dotProduct(const SDL_FPoint& A, const SDL_FPoint& B)
{
	return A.x * B.x + A.y * B.y;
}