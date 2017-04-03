#pragma once

#include "glut_config.h"

#include "Ball.hpp"

class Graphics {
public:
	static void Init(int &argc, char **argv);
	static void Quit();
	static void DisplayText(float x, float y, const char *s);
	static void DisplayObject(Ball ball, GLuint id, double degree);
private:
	static void Display();
	static void Timer(int);
	static void Keyboard(unsigned char key, int x, int y);
	static void Special(int key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void Reshape(int new_width, int new_height);
};
