#pragma once
#include "stdafx.h"

class Paddle
{
private:
	int padheight;
	int padwidth;
	int padpos_x;
	int padpos_y;
	int pad_speed;
	int width;
	int height;

public:
	Paddle(int wide, int high, int posx, int posy, int speed) {
		padheight = high;
		padwidth = wide;
		padpos_x = posx;
		padpos_y = posy;
		pad_speed = speed;
	}

	int getPaddlePosx();
	int getPaddlePosy();
	int getPaddleWidth();
	int getPaddleHeight();
	void movePaddleVertical(bool);
};