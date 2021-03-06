#include "paddle.h"

Paddle::Paddle(){
	y = 186;
	x = 118;
	width = 36;
	height = 4;
	move_speed = 5;
}
void Paddle::SetX(int newx){
	x = newx;
	if ((x + width) > 256) x = 256 - width;
}
void Paddle::MoveLeft(){
	x -= move_speed;
	if (x < 0) x =0;
}
void Paddle::MoveRight(){
	x += move_speed;
	if ((x + width) > 256) x = 256 - width;
}
void Paddle::Draw(){
	glBoxFilled(x, y, x + width, y + height, RGB15(26,0,0));
	glBox(x,y,x+width,y+height,RGB15(31,0,0));
}

bool Paddle::Collides(int nx,int ny,int w,int h)
{
	return ((x + width) > nx
    	&& x < (nx + w)
    	&& (y + height) > ny
    	&& y < (ny + h));
}
void Paddle::Update(){

}