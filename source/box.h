#include <nds.h>
#include <gl2d.h>
#include <nds/arm9/sound.h>
#include <stdio.h>
#include <vector>

class Box
{
	private:
		float x, y,x2,y2;
		int width, height;
		float xspeed, yspeed;
		int cols[4];
	public:
		Box();
		void RandomiseColours();
		bool Update();
		void Draw(bool);
		void Randomise();
		void AdjustSpeed(int);
		void DecreaseSize(int,int);
		void IncreaseSize(int,int);
		void PrintDebugInfo();
};