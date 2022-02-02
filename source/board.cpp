#include "board.h"

Board::Board(){
	ball = new Ball;
	offsetX = 0;
	offsetY = 16;
	x = 0;
	y = 150;
	for (int i =0; i < board_width;i++){
		for (int j = 0; j < board_height; j++){
			brick_state[i][j] = true;
		}
	}
}

void Board::Update(){
	for (int i =0 ; i < board_width; i++){
		for (int j =0 ; j < board_height; j++){
			
			if (brick_state[i][j]){
				float brick_x = offsetX + x + i*brick_width;
				float brick_y = offsetY + y + j*brick_height;
				float brick_centre_x = brick_x + 0.5f*brick_width;
				float brick_centre_y = brick_y + 0.5f*brick_height;

				float ball_centre_x = ball->x + 0.5f*ball->width;
				float ball_centre_y = ball->y + 0.5f*ball->height;

			}
		}
	}
}