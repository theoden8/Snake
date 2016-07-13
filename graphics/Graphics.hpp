#pragma once

#include "glut_config.h"
#include "opengl_config.h"

#include "State.hpp"
#include "Ball.hpp"

class State;

class Graphics {
public:
	static void SetOpenGLContext(int &argc, char **argv);
	static void SetOpenGLFunctions();
	static void StartGraphics();

	static void DrawText(float x, float y, char *s);
	static void DrawObject(int x, int y, GLuint id, double degree);

private:
	static void Display();
	static void Timer(int);
	static void Keyboard(unsigned char key, int x, int y);
	static void Special(int key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void Reshape(int new_width, int new_height);
};
