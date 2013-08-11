#include "SDL.h"
#include "Renderer.h"

class pCollectible{
public:
	pCollectible(SDL_Surface*);
	SDL_Rect* box;
	SDL_Surface* sprite;

	void draw(SDL_Surface*);
};