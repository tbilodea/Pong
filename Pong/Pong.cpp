// Pong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <sstream>
#include <math.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL/freeglut.h"
#pragma comment(lib, "OpenGL32.lib")

//window size
int height = 200;
int width = 500;
int interval = 1000/60; //fps 60

//score
int score_left = 0;
int score_right = 0;
int racket_width = 10;
int racket_height = 80;
int racket_speed = 3;

//left racket pos
float racket_left_x = 10.0f;
float racket_left_y = 50;

//right racket pos
float racket_right_x = width - racket_width - 10;
float racket_right_y = 50;

void keyboard() {
	//left racket
	if (GetAsyncKeyState('W') & 0x8000) racket_left_y += racket_speed;
	if (GetAsyncKeyState('S') & 0x8000) racket_left_y -= racket_speed;
	//right racket
	if (GetAsyncKeyState(VK_UP)) racket_right_y += racket_speed;
	if (GetAsyncKeyState(VK_DOWN)) racket_right_y -= racket_speed;
}

void drawRect(float x, float y, float width, float height) {
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void drawText(float x, float y, std::string text) {
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}
void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Draw the scene
	//Draw the rackets
	drawRect(racket_left_x, racket_left_y, racket_width, racket_height);
	drawRect(racket_right_x, racket_right_y, racket_width, racket_height);

	//drawscore
	std::ostringstream score;
	score << score_left << ":" << score_right;
	drawText(width / 2 - 10, height - 15, score.str());
	
	//swap buffers
	glutSwapBuffers();
}

void update(int value) {
	keyboard();

	glutTimerFunc(interval, update, 0); //call update in an interval
	//redisplay
	glutPostRedisplay();
}

void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int _tmain(int argc, char** argv)
{
	//open a window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Pongish!");

	//Register Callback Functions
	glutDisplayFunc(draw);
	glutTimerFunc(interval, update, 0);

	//set scene
	enable2D(width, height);
	glColor3f(1.0f, 1.0f, 1.0f);

	//start
	glutMainLoop();

	return 0;
}