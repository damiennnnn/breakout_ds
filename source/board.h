#include "includes.h"
#include "ball.h"
#include "paddle.h"
#define board_width 8
#define board_height 10
#define brick_width 32
#define brick_height 10

class Board
{
private:
	bool brick_state[board_width][board_height];
	int brick_col[board_width][board_height];
	int alive_count, max_count;
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

	int level; 
	void SetLevel(int);
	void AdjustPaddleSpeed(int);
	void AdjustBallSpeed(float);
	void PaddleMove(int);
	void PaddleSetX(int);
	int BallGetX();
	void PrintDebugInfo();
};