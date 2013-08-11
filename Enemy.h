#include "SDL.h"
#include "Vector2.h"

class Enemy{
public:
	Enemy(); //number one!
	Enemy(int, int);
	float speed;

	SDL_Rect box;
	Vector2 velocity;
	SDL_Surface* sprite;

	void incrementSpeed(float); // in order to keep velocity in it's normal spot
	void setSpeed(float);       //same reason
};