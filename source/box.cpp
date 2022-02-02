#include "box.h"


Box::Box(){
	width = 50;
	height = 20;
}

void Box::RandomiseColours(){
	for (int i=0;i<4;i++)
		cols[i] = RGB15(rand()%255, rand()%255,rand()%255);
}
void Box::Randomise(){
	RandomiseColours();
}
void Box::AdjustSpeed(int i){
	if (i == 0){ // decrease
		xspeed += (xspeed < 0) ? 0.01f : -0.01f;
		yspeed += (yspeed < 0) ? 0.01f : -0.01f;
	}
	else{ // increase
		xspeed += (xspeed < 0) ? -0.01f : 0.01f;
		yspeed += (yspeed < 0) ? -0.01f : 0.01f;
	}
}
bool Box::Update(){
	bool _collided = false;
	x2 = (x + width);
	y2 = (y + height);

	if (x2 >= 256 || x <= 0) {
		xspeed *= -1; 
		_collided = true;
		RandomiseColours();}
			// invert our speed value and set a random colour for the box
	if (y2 >= 192 || y <= 0) {
		yspeed *= -1; 
		_collided = true;
		RandomiseColours();}

	x += xspeed;
	y += yspeed;
	return _collided;
}
void Box::DecreaseSize(int x, int y){
	if (width > 1) width -= x;
	if (height > 1) height -= y; 
}
void Box::IncreaseSize(int x, int y){
	width += x;
	height += y;
}
void Box::Draw(bool gradient){
	if (gradient)
		glBoxFilledGradient(x,y,x2,y2, cols[0],cols[1],cols[2],cols[3]); // draw our box wit gradient
	else
		glBoxFilled(x,y,x2,y2,cols[0]); // draw our box solid fill

	//glLine(x, y, x2, y2, cols[1]);
	//glLine(x2, y2, x, y, cols[1]);
}
void Box::PrintDebugInfo(){
	printf("\x1b[17;0Hw: %d h: %d        ", width, height);
	printf("\x1b[18;0Hxspeed: %f        ", xspeed);
	printf("\x1b[19;0Hyspeed: %f        ", yspeed);
	printf("\x1b[20;0Hx: %f y: %f        ", x, y);
}