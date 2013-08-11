#include "Player.h"

/*class Player{
	Vector2 position;
	Vector2 velocity;
	SDL_Surface* sprite;
	void handle_input(SDL_Event);
};*/

Player::Player(){
	Vector2 vel(0.0,0.0);
	speed = 5.0f;
	
	//set up bounding box
	box.w = 20.0f;
	box.h = 20.0f;
	box.x = 0.0f;
	box.y = 0.0f;

	velocity = vel;
	sprite = NULL;
}

Player::Player(float x, float y, float xVel, float yVel, float width, float height, SDL_Surface* sprite){
	velocity.x = xVel;
	velocity.y = yVel;

	(*this).sprite = sprite;

	//set up bounding box
	box.w = (*sprite).w;
	box.h = (*sprite).h;
	box.x = x;
	box.y = y;
}

void Player::handle_input(SDL_Event e){
	//on key down
	if(e.type == SDL_KEYDOWN){
		switch(e.key.keysym.sym){
			case SDLK_w: velocity.y  -= speed; break;
			case SDLK_s: velocity.y += speed; break;
			case SDLK_a: velocity.x -= speed; break;
			case SDLK_d: velocity.x += speed; break;
		}
	}

	//do the opposite when releasing
	if(e.type == SDL_KEYUP){
		switch(e.key.keysym.sym){
			case SDLK_w: velocity.y += speed; break;
			case SDLK_s: velocity.y -= speed; break;
			case SDLK_a: velocity.x += speed; break;
			case SDLK_d: velocity.x -= speed; break;
		}
	}
}