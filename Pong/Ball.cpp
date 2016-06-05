#include "stdafx.h"
#include "Ball.h"
#include "Pong.h"

//updateBall determines ball direction based on its environment
//Where P1 is the LEFT Paddle and P2 is the RIGHT Paddle
void Ball::updateBall(Paddle P1, Paddle P2) {
	//fly in a direction
	ball_pos_x += ball_dir_x * ball_speed;
	ball_pos_y += ball_dir_y * ball_speed;

	//left racket
	if (ball_pos_x < P1.getPaddlePosx() + P1.getPaddleWidth() &&
		ball_pos_x > P1.getPaddlePosx() &&
		ball_pos_y < P1.getPaddlePosy() + P1.getPaddleHeight() &&
		ball_pos_y > P1.getPaddlePosy()) {
		//set fly depending on where it hits the paddle
		float t = ((ball_pos_y - P1.getPaddlePosy()) / P1.getPaddleHeight()) - 0.5f;
		ball_dir_x = fabs(ball_dir_x);
		ball_dir_y = t;
	}

	//right racket
	if (ball_pos_x > P2.getPaddlePosx() &&
		ball_pos_x < P2.getPaddlePosx() + P2.getPaddleWidth() &&
		ball_pos_y < P2.getPaddlePosy() + P2.getPaddleHeight() &&
		ball_pos_y > P2.getPaddlePosy()) {
		//set fly depending on where it hits the paddle
		float t = ((ball_pos_y - P2.getPaddlePosy()) / P2.getPaddleHeight()) - 0.5f;
		ball_dir_x = -fabs(ball_dir_x);
		ball_dir_y = t;
	}

	//top barrier
	if (ball_pos_y > height) {
		ball_dir_y = -fabs(ball_dir_y);
	}
	//bottom barrier
	if (ball_pos_y < 0) {
		ball_dir_y = fabs(ball_dir_y);
	}

	//make the direction values normal
	float sqxy = sqrt(ball_dir_x*ball_dir_x + ball_dir_y*ball_dir_y);
	if (sqxy != 0.0f) {
		ball_dir_x = ball_dir_x / sqxy;
		ball_dir_y = ball_dir_y / sqxy;
	}
}


int Ball::getBallPosx(){
	return ball_pos_x;
}

int Ball::getBallPosy() {
	return ball_pos_y;
}

int Ball::size() {
	return ball_size;
}

void Ball::resetBall(bool headedRight) {
	ball_pos_x = width / 2;
	ball_pos_y = height / 2;
	ball_dir_y = 0.0f;

	if (headedRight) {
		ball_dir_x = 1.0f;
	} else {
		ball_dir_x = -1.0f;
	}
}