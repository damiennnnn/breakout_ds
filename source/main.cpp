/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $
	Atari Breakout clone for nintendo DS -- damien


---------------------------------------------------------------------------------*/
#include "includes.h"
#include "board.h"
//---------------------------------------------------------------------------------

int g_vol = 0;
int main(void) {
//---------------------------------------------------------------------------------
	videoSetMode(MODE_5_3D);
	consoleDemoInit();
	glScreen2D();
	soundEnable();
	int sound_id = soundPlayNoise(7000, g_vol, 64);
	Board board;
	
	while(1) {
		glBegin2D();		
		scanKeys();

		touchPosition data;
		touchRead(&data);
		int keys = keysDownRepeat();
		if (keys & KEY_L)
			board.PaddleMove(0);
		if (keys & KEY_R)
			board.PaddleMove(1);
		if (keys & KEY_LEFT)
			board.AdjustBallSpeed(-1);
		if (keys & KEY_RIGHT)
			board.AdjustBallSpeed(1);

		if (data.px > 0)
			board.PaddleSetX(data.px);

		if (board.Update())
			g_vol = 64;
		board.Draw();
		printf("\x1b[2;0Hatari breakout - damien :)");
		printf("\x1b[3;0HL + R to move left and right");
		printf("\x1b[4;0Hor use touchscreen to move");
		printf("\x1b[6;0Htouch x: %d y: %d          ", data.px, data.py);
		printf("\x1b[7;0Hvolume: %d          ", g_vol);

		board.PrintDebugInfo();

		soundSetVolume(sound_id, g_vol);
		g_vol -= 4;
		if (g_vol < 0) g_vol = 0;
		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}
