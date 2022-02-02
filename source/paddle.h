#include "includes.h"

class Paddle
{
private:
public:
	int move_speed;
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