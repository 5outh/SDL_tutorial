#include "Vector2.h"
#include <math.h>

Vector2::Vector2(){
	x = y = 0;
}

Vector2::Vector2(float a, float b){
	x = a;
	y = b;
}


Vector2 Vector2::negate(){
	Vector2 v(-x, -y);
	return v;
}

float Vector2::dot(Vector2 v){
	return x * v.x + y * v.y;
}

Vector2 Vector2::add(Vector2 v){
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::subt(Vector2 v){
	Vector2 neg = v.negate();
	Vector2 self = *this;
	return self.add(v.negate());
}

float Vector2::length(){
	return sqrt(x*x + y*y);
}