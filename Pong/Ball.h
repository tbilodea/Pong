#pragma once
#include "stdafx.h"
#include "Paddle.h"
//Ball class to track the pong ball

class Ball
{

private:
	float ball_pos_x;
	float ball_pos_y;
	float ball_dir_x;
	float ball_dir_y;
	int ball_size;
	int ball_speed;
	int height;
	int width;

public:
	Ball(float ballPosX, float ballPosY, float ballDirX, float ballDirY, int bsize, int bspeed) {
		ball_pos_x=ballPosX;
		ball_pos_y = ballPosY;
		ball_dir_x = ballDirX;
		ball_dir_y = ballDirY;
		ball_size = bsize;
		ball_speed = bspeed;
	}
	void updateBall(Paddle,Paddle);
	int getBallPosx();
	int getBallPosy();
	int size();
	void resetBall(bool);
};