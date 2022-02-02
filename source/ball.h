#include "includes.h"

class Ball
{
private:

public:
	Ball();
	void Draw();
	void Update();
	void SetDirection(float dirx, float diry);
	float x, y;

	float ball_speed;
	float dirx, diry;
	int width, height;
};
