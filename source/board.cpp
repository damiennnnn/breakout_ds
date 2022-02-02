#include "board.h"

Board::Board(){
	Init();
}

void Board::Init(){
	ball = new Ball;
	paddle = new Paddle;
	offsetX = 0;
	offsetY = 16;
	x = 0;
	y = 0;
	score = 0;
	for (int i =0; i < board_width;i++){
		for (int j = 0; j < board_height; j++){
			brick_state[i][j] = true; // initialise game board
			brick_col[i][j] = RGB15(rand()%255,rand()%255,rand()%255);
		}
	}
}

void Board::PaddleSetX(int newx){
	paddle->SetX(newx);
}
void Board::PaddleMove(int dir){
	// 0 = left 1 = right
	if (dir > 0)
		paddle->MoveRight();
	else
		paddle->MoveLeft();
}

void Board::Draw(){
	for (int i =0 ; i < board_width; i++){
		for (int j = 0; j < board_height; j++){
			if (brick_state[i][j]){
				float brick_x = offsetX + x + i*brick_width;
				float brick_y = offsetY + y + j*brick_height;
				float brick_x2 = (brick_x + brick_width);
				float brick_y2 = (brick_y + brick_height);
				glBoxFilled(brick_x, brick_y, brick_x2, brick_y2, brick_col[i][j]);
			}
		}
	}
	ball->Draw(); // draw ball
	paddle->Draw(); // draw paddle
}

void Board::BallBrickResponse(int dir_index){
    int mulx = 1;
    int muly = 1;
 
    if (ball->dirx > 0) {
        if (ball->diry > 0) {
            if (dir_index == 0 || dir_index == 3) {
                mulx = -1;
            } else {
                muly = -1;
            }
        } else if (ball->diry < 0) {
            if (dir_index == 0 || dir_index == 1) {
                mulx = -1;
            } else {
                muly = -1;
            }
        }
    } else if (ball->dirx < 0) {
        if (ball->diry > 0) {
            if (dir_index == 2 || dir_index == 3) {
                mulx = -1;
            } else {
                muly = -1;
            }
        } else if (ball->diry < 0) {
            if (dir_index == 1 || dir_index == 2) {
                mulx = -1;
            } else {
                muly = -1;
            }
        }
    }
    ball->SetDirection(mulx*ball->dirx, muly*ball->diry);
}

bool Board::PaddleCollision(){
	float ball_centre_x = ball->x + ball->width/2.0f;
	if (paddle->Collides(ball->x, ball->y, ball->width, ball->height)){
		ball->y = paddle->y - ball->height;

		float hit_x = (ball_centre_x - paddle->x);
		if (hit_x < 0) hit_x = 0;
		else if (hit_x > paddle->width)
			hit_x = paddle->width;
		hit_x -= paddle->width / 2.0f;
		float x_dir = 2.0f * (hit_x / (paddle->width / 2.0f));

		ball->SetDirection(x_dir, -1);
		return true;
	}

	return false;
}

bool Board::BoardCollision(){
	bool _collide = false;
    if (ball->y < 0) {
        ball->y = 0;
        ball->diry *= -1; _collide=true;
    } else if ((ball->y + ball->height) > 192) {
    	// dead ball, reset;
    	Init();
    }

    if (ball->x <= 0) {
        ball->x = 0;
        ball->dirx *= -1;
        _collide=true;
    } else if (ball->x + ball->width >= 256) {
        ball->x = 256 - ball->width;
        ball->dirx *= -1;
        _collide=true;
    }

    return _collide;
}
bool Board::Tick(){
	for (int i =0 ; i < board_width; i++){
		for (int j =0 ; j < board_height; j++){		
			if (brick_state[i][j]){
				float brick_x = offsetX + x + i*brick_width;
				float brick_y = offsetY + y + j*brick_height;
				float brick_centre_x = brick_x + 0.5f*brick_width;
				float brick_centre_y = brick_y + 0.5f*brick_height;

				float ball_centre_x = ball->x + 0.5f*ball->width;
				float ball_centre_y = ball->y + 0.5f*ball->height;

				if (ball->x <= (brick_x + brick_width)
					&& (ball->x + ball->width) >= brick_x
					&& ball->y <= (brick_y + brick_height)
					&& (ball->y + ball->height) >= brick_y){
						brick_state[i][j] = false; // collision

					float y_min = 0;
					if (brick_y > ball->y){
						y_min = brick_y;
					}
					else
					{
						y_min = ball->y;
					}

					float y_max = 0;
					if ((brick_y + board_height) < (ball->y + ball->height)){
						y_max = brick_y + brick_height;
					}
					else
					{
						y_max = ball->y + ball->height;
					}

					float y_size = y_max - y_min;

					float x_min = 0;
					if (brick_x > ball->x){
						x_min = brick_x;
					}
					else{
						x_min = ball->x;
					}

					float x_max = 0;
					if (brick_x + brick_width < (ball->x + ball->width)){
						x_max = brick_x + brick_width;
					}
					else
					{
						x_max = ball->x + ball->width;
					}

					float x_size = x_max - x_min;

					if (x_size > y_size) {
                        if (ball_centre_y > brick_centre_y) {
                            // Bottom
                            ball->y += y_size + 0.01f;
                            BallBrickResponse(3);
                        } else {
                            // Top
                            ball->y -= y_size + 0.01f; 
                            BallBrickResponse(1);
                        }
                    } else {
                        if (ball_centre_x < brick_centre_x) {
                            // Left
                            ball->x -= x_size + 0.01f;
                            BallBrickResponse(0);
                        } else {
                            // Right
                            ball->x += x_size + 0.01f;
                            BallBrickResponse(2);
                        }
                    }
                    return true;
				}
			}
		}
	}
	return false;
}
bool Board::Update(){
	bool _boardcollide = BoardCollision();
	bool _paddlecollide = PaddleCollision();
	bool _brickcollide = Tick();
	ball->Update();
	paddle->Update();
	if (_brickcollide) {score++; AdjustBallSpeed(1.0f);};
	return (_brickcollide || _boardcollide || _paddlecollide);
}

void Board::AdjustPaddleSpeed(int s){
	paddle->move_speed += s;
}
void Board::AdjustBallSpeed(float s){
	ball->ball_speed += s;
}
void Board::PrintDebugInfo()
{
	printf("\x1b[12;0H ball x: %f          ", ball->x);
	printf("\x1b[13;0H ball y: %f          ", ball->y);
	printf("\x1b[14;0H ball speed: %f          ", ball->ball_speed);
	printf("\x1b[15;0H paddle speed: %d          ", paddle->move_speed);
	
	printf("\x1b[16;0H score: %d          ", score);
	
}