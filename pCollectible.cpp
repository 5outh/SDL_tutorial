#include "pCollectible.h"
#include <time.h>

pCollectible::pCollectible(SDL_Surface* spr){
	srand(time(NULL));
	SDL_Rect* b = new SDL_Rect;
	box = b;
	box->x = (rand() % 31) * 20; // random multiple of 20 between 0 and 620
	box->y = (rand() % 23) * 20; // random multiple of 20 between 0 and 460
	box->w = 20;
	box->h = 20;
	sprite  = spr;
}

void pCollectible::draw(SDL_Surface* destination){
	Renderer::apply_surface(box->x, box->y, sprite, destination);
}