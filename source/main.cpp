/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $
	Atari Breakout clone for nintendo DS -- damien


---------------------------------------------------------------------------------*/
#include "includes.h"
#include "paddle.h"
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	videoSetMode(MODE_5_3D);
	consoleDemoInit();
	glScreen2D();
	soundEnable();
	int vol = 0;

	//int sound_id = soundPlayNoise(7000, vol, 64);

	
	while(1) {
		glBegin2D();		
		scanKeys();

		int keys = keysDown();




		printf("\x1b[2;0Hbouncing dvd test - damien :)");
		printf("\x1b[4;0Hpress A to randomise");
		printf("\x1b[5;0HL + R to adjust speed");
		printf("\x1b[6;0HLeft + Right to adjust width");
		printf("\x1b[7;0HUp + Down to adjust height");
		printf("\x1b[8;0HSELECT to reset values");
		printf("\x1b[9;0HSTART to switch colour mode");
		printf("\x1b[10;0HY to create new box, X to remove");

		printf("\x1b[12;0H volume: %d        ", vol);

		//soundSetVolume(sound_id, vol);
		vol -= 8;
		if (vol < 0) vol = 0;
		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}
