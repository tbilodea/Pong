// Pong.cpp : Defines the entry point for the console application.
//
//TO DO: Make a Draw class that is inherited by all objects (or figure out a better way to recursively draw the screen in OpenGL)
// Make it so multiple Balls can appear
// Make a real menu system (you're going to have to go think about that one)

#include "stdafx.h"

#pragma comment(lib, "OpenGL32.lib")

#include "Ball.h"
#include "Paddle.h"
#include "Pong.h"


//window size
int screenWidth = 500;
int screenHeight = 200;
int interval = 1000/60; //fps 60

bool flagStart = true; //splashscreen & pausescreen flag

//score
int score_left = 0;
int score_right = 0;

//racket variables
int racket_width = 5;
int racket_height = 40;
int racket_speed = 1;

//left racket pos
float racket_left_x = 10.0f;
float racket_left_y = screenHeight/2;

//right racket pos
float racket_right_x = screenWidth - racket_width;
float racket_right_y = screenHeight/2;

//creating a Ball, and Paddle objects --!Ball will need to be changed in the future to be destructible for powerups
Ball ball1 = Ball(screenWidth/2,screenHeight/2,-1.0f,0.0,3,3);
Paddle Paddle_Left = Paddle(racket_width, racket_height, racket_left_x, racket_left_y, racket_speed);
Paddle Paddle_Right = Paddle(racket_width, racket_height, racket_right_x, racket_right_y, racket_speed);

//checks for keyboard presses continuously
void keyboard() {
	//pausing the game
	if (GetAsyncKeyState('P')) flagStart = true;
	//left racket moved
	if (GetAsyncKeyState('W')) Paddle_Left.movePaddleVertical(true);
	if (GetAsyncKeyState('S')) Paddle_Left.movePaddleVertical(false);
	//right racket moved
	if (GetAsyncKeyState(VK_UP)) Paddle_Right.movePaddleVertical(true);
	if (GetAsyncKeyState(VK_DOWN)) Paddle_Right.movePaddleVertical(false);
}

//draws a rectangle (paddles and ball) --!to be revised into an inherited class for paddles and ball
void drawRect(float x, float y, float width, float height) {
	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
	glEnd();	
}

//Draws "text" at x, y coordinates
void drawText(float x, float y, std::string text) {
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
}

//called continuously to update the field drawings
void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//check if not paused
	if (!flagStart) {
		//Draw the rackets
		drawRect(Paddle_Left.getPaddlePosx(), Paddle_Left.getPaddlePosy(), Paddle_Left.getPaddleWidth(), Paddle_Left.getPaddleHeight());
		drawRect(Paddle_Right.getPaddlePosx(), Paddle_Right.getPaddlePosy(), Paddle_Right.getPaddleWidth(), Paddle_Right.getPaddleHeight());
		//drawscore
		std::ostringstream score;
		score << score_left << ":" << score_right;
		drawText(screenWidth / 2 - 10, screenHeight - 15, score.str());
		//drawball
		drawRect(ball1.getBallPosx() - ball1.size() / 2, ball1.getBallPosy() - ball1.size() / 2, ball1.size(), ball1.size());
	}else{ //if paused
		glRasterPos2f(screenWidth /4, screenHeight * 3 / 4); //position of text
		std::string Welcome;
		Welcome = "PONG!\nControls are W,S for left side, Up and Down arrows for the right.\nPress P to pause, ESC to quit.\n\nPUSH SPACE TO CONTINUE!";
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)Welcome.c_str());
	}
	glutSwapBuffers(); //swap Buffers
}

//sets which way ball will go after reset and increments the score
bool checkScore() {
	//left wall
	if (ball1.getBallPosx() < 0) {
		++score_right;
		ball1.resetBall(true);//reset the direction toward +x
		return true;
	}
	else if(ball1.getBallPosx() > screenWidth) {
		++score_left;
		ball1.resetBall(false);
		return true;
	}else{
		return false;
	}
}

//update function that tells system when next to update
void update(int value) {
	if (GetAsyncKeyState(VK_SPACE)) flagStart = false; //check if we are resuming
	if (GetAsyncKeyState(VK_ESCAPE)) glutDestroyWindow(glutGetWindow()); //exit glloop
	//check splashscreen or pause
	if (flagStart == false) {
		keyboard(); //update keypress
		ball1.updateBall(Paddle_Left,Paddle_Right); //update ball
		checkScore(); //check if the ball has scored
	}

	glutTimerFunc(interval, update, 0); //call update in an interval
	//redisplay
	glutPostRedisplay();
}

void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION); //set projection matrix
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f); //dims of matrix
	glMatrixMode(GL_MODELVIEW); //sets matrix
	glLoadIdentity();
	glutFullScreen();
}

int _tmain(int argc, char** argv)
{
	//open a window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Pong-ish!");

	//Register Callback Functions
	glutDisplayFunc(draw);
	glutTimerFunc(interval, update, 0); //glutMainLoop goes to update at interval

	//set scene
	enable2D(screenWidth, screenHeight);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	//start
	glutMainLoop();

	return 0;
}