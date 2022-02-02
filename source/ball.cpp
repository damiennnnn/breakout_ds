#include "ball.h"
#include <cmath>
Ball::Ball()
{
	ball_speed = 2;
	x =160; y =160 ;
	width = 4; 
	height = 4;
	SetDirection(-1,1);
}
void Ball::Update(){
	x += dirx * 0.01f;
    y += diry * 0.01f;
}
void Ball::Draw(){
	glBoxFilled(x, y, x + width, y + height, RGB15(255,255,255));
}
void Ball::SetDirection(float dirx, float diry){
	float lengthsquare = (dirx * dirx + diry * diry);
	long lengthsqint = (long)(lengthsquare * 10000.0f);
	long lengthroot = sqrt64(lengthsqint);
    float length = ((float)lengthroot / 10000.0f);
    this->dirx = ball_speed	 * (dirx / length);
    this->diry = ball_speed * (diry / length);
}