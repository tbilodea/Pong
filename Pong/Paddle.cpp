#include "stdafx.h"
#include "Paddle.h"
#include "Pong.h"

//called upon keypress command for one of the paddles
void Paddle::movePaddleVertical(bool up) {
	if (up) { //if button was to go up
		if (padpos_y < screenHeight-padheight) { //check if the paddle is at the top
			padpos_y += pad_speed;
		}
	}else{ //else try to go down
		if (padpos_y > 0) {
			padpos_y -= pad_speed;
		}
	}
}

//get positions for ball updating
float Paddle::getPaddlePosx() {
	return padpos_x;
}
float Paddle::getPaddlePosy() {
	return padpos_y;
}
int Paddle::getPaddleWidth() {
	return padwidth;
}
int Paddle::getPaddleHeight() {
	return padheight;
}