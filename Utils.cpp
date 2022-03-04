#include <SDL.h>
#include "Utils.h"

float utils::hireTimeInSeconds()
{
	float t = SDL_GetTicks();
	t *= 0.001f;
	return t;
}