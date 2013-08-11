#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Renderer{
public:
	static SDL_Surface* load_image(std::string);
	static void apply_surface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect* clip = NULL);
	static void render_rectangle(SDL_Surface*, SDL_Rect*);
};

#endif