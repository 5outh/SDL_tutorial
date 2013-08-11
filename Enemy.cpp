#include "Enemy.h"

Enemy::Enemy(){
	speed = 1.0f;

	box.h = 20;
	box.w = 20;
	box.x = 400;
	box.y = 200;

	Vector2 vel(speed,speed);
	velocity = vel;

	sprite = NULL;
};

Enemy::Enemy(int xCoord, int yCoord){
	speed = 1.0f;

	box.h = 20;
	box.w = 20;
	box.x = xCoord;
	box.y = yCoord;

	Vector2 vel(speed,speed);
	velocity = vel;

	sprite = NULL;
}

void Enemy::setSpeed(float s){
	speed = s;
	if(velocity.x < 0){
		velocity.x = -speed;
	}else{
		velocity.x = speed;
	}
	if(velocity.y < 0){
		velocity.y = -speed;
	}else{
		velocity.y = speed;
	}
}


void Enemy::incrementSpeed(float s){
	if(speed < 8.0f){
		speed += s;
		if(velocity.x < 0){
			velocity.x -= speed;
		}else{
			velocity.x += speed;
		}
		if(velocity.y < 0){
			velocity.y -= speed;
		}else{
			velocity.y += speed;
		}
	}
}