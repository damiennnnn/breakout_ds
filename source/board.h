#include "includes.h"
#include "ball.h"
#include "paddle.h"
#define board_width 12
#define board_height 16
#define brick_width 24
#define brick_height 6

class Board
{
private:
	bool brick_state[board_width][board_height];
	int brick_col[board_width][board_height];
	Ball* ball;
	Paddle* paddle;
	float offsetX, offsetY;
	int x, y;

	int score;
	void BallBrickResponse(int);
	bool BoardCollision();
	bool PaddleCollision();
	bool Tick();
	void Init();
public:
	Board();
	bool Update();
	void Draw();

	void AdjustBallSpeed(float);
	void PaddleMove(int);
	void PaddleSetX(int);
	void PrintDebugInfo();
};