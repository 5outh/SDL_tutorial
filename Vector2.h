#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2{
public:
	Vector2();
	Vector2(float, float);
	float x, y;
	float dot(Vector2);
	float length();
	Vector2 add(Vector2);
	Vector2 subt(Vector2);
	Vector2 negate();
};

#endif