#include <list>
#include "pSnakeSegment.h"
#include "Renderer.h"

class pSnake{
public:
	pSnake();
	std::list<pSnakeSegment> segments; //segments of the snake
	SDL_Surface* segment_sprite;

	void update(Direction); // update snake based on direction
	void move(); // move snake
	void handle_input(SDL_Event*); //update snake based on user input
	bool is_colliding(); // is the snake colliding with itself?
	void add_segment();
	void draw(SDL_Surface*);
};