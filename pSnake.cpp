#include "pSnake.h"
#include "Windows.h"
#include <sstream>

pSnake::pSnake(){
	pSnakeSegment segment;

	segment.direction = RIGHT;

	segment.xVelocity = 1;
	segment.yVelocity = 0;

	segment.box->x = 320;
	segment.box->y = 240;
	
	segments.push_back(segment); //make new segment in the beginning of the screen
	
	segment_sprite = NULL; //set in snake class, for some reason this doesn't really work.
}

void pSnake::handle_input(SDL_Event* e){
	if(e->type == SDL_KEYDOWN){
		switch(e->key.keysym.sym){
			case SDLK_UP: update(UP); break;
			case SDLK_DOWN: update(DOWN); break;
			case SDLK_LEFT: update(LEFT); break;
			case SDLK_RIGHT: update(RIGHT); break;
		}
	}
}

//this definitely works correctly
void pSnake::update(Direction d){
	std::list<Direction> directions;

	for(std::list<pSnakeSegment>::iterator it = segments.begin(); it != segments.end(); it++){ //collect directions of segments
		directions.push_back(it->direction);
	}

	directions.push_front(d); //change front direction and shift the rest one back
	directions.pop_back();

	for(std::list<pSnakeSegment>::iterator it = segments.begin(); it != segments.end(); it++){
		it->direction = directions.front();
		directions.pop_front();
		it->update();
	}
}

void pSnake::move(){ //ALTERNATIVE to add_segment
	for(std::list<pSnakeSegment>::iterator it = segments.begin(); it != segments.end(); it++){
		it->move(); //move each segment based on it's individual direction
	}
}

void pSnake::add_segment(){ //ALTERNATIVE to move()
	pSnakeSegment back = segments.back(); //last segment
	pSnakeSegment back_cpy;

	back_cpy.box->x = back.box->x;
	back_cpy.box->y = back.box->y;
	back_cpy.box->w = back.box->w;
	back_cpy.box->h = back.box->h;
	back_cpy.direction = back.direction;
	back_cpy.xVelocity = back.xVelocity;
	back_cpy.yVelocity = back.yVelocity;

	move(); // move all segments
	segments.push_back(back_cpy); //push copy of last segment to end of snake
}

bool pSnake::is_colliding(){
	//front segment of the snake
	int headX = segments.front().box->x;
	int headY = segments.front().box->y;

	for(std::list<pSnakeSegment>::iterator it = ++segments.begin(); it != segments.end(); it++){
		int x = it->box->x;
		int y = it->box->y;
		if(headX == x && headY == y){
			return true; //at least one segment is colliding with the head of the snake
		}
	}

	return false; //not colliding
}

void pSnake::draw(SDL_Surface* destination){
	for(std::list<pSnakeSegment>::iterator it = segments.begin(); it != segments.end(); it++){
		Renderer::apply_surface(it->box->x, it->box->y, segment_sprite, destination);
	}
}