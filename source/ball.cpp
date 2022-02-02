#include "ball.h"
#include <cmath>
Ball::Ball()
{
	ball_speed = 128;
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
    float length = sqrt(dirx * dirx + diry * diry);
    this->dirx = ball_speed	 * (dirx / length);
    this->diry = ball_speed * (diry / length);
}