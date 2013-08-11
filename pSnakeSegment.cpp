#include "pSnakeSegment.h"
#include "SDL.h"

pSnakeSegment::pSnakeSegment(){
	SDL_Rect* b = new SDL_Rect;
	box = b;
	box->w = 20;
	box->h = 20;
	direction = RIGHT;
	//x and y coordinates will be set in the pSnake class
}

void pSnakeSegment::update(){
	xVelocity = 0;
	yVelocity = 0; //reset velocity

	//change direction of segment
	switch(direction){
		case DOWN : yVelocity += 1; break;
		case UP   : yVelocity -= 1; break;
		case RIGHT: xVelocity += 1; break;
		case LEFT : xVelocity -= 1; break;
	}
};

void pSnakeSegment::move(){
	//move segments one square in their direction
	box->x += xVelocity * box->w;
	box->y += yVelocity * box->h;
}