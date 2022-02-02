#include "includes.h"

class Paddle
{
private:
	int move_speed;
public:
	int x, y;
	int width, height;
	Paddle();
	void Draw();
	void Update();
	void MoveLeft();
	void MoveRight();

	bool Collides(int,int,int,int);
	void SetX(int);
};