#include "includes.h"
#include "ball.h"

#define board_width 12
#define board_height 12
#define brick_width 16
#define brick_height 6

class Board
{
private:
	bool brick_state[board_width][board_height];
	Ball* ball;
	float offsetX, offsetY;
	int x, y;
public:
	Board();
	void Update();
	void Draw();
};