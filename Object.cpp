#include "Object.h"

void Object::setSurface(SDL_Surface* new_surface)
{
	if (new_surface)
		surface = new_surface;
}