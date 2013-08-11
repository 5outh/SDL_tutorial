#include "Vector2.h"
#include "SDL.h"

class Player{
public:
	Player();
	Player(float x, float y, float xVel = 0, float yVel = 0, float width = 0, float height = 0, SDL_Surface* sprite = NULL);

	SDL_Rect box; //x, y, width, height

	Vector2 velocity;
	float speed;

	SDL_Surface* sprite;
	void handle_input(SDL_Event);
};