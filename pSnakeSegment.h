#include "SDL.h"
#include "Direction.h"
#include "Renderer.h"

class pSnakeSegment{
public:
	pSnakeSegment();
	
	Direction direction;

	int xVelocity;
	int yVelocity;
	
	SDL_Rect* box;

	void update(); //update velocity 
	void move(); //move snake segment
};