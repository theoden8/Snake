#pragma once

#include "glut_config.h"
#include "opengl_config.h"

#include "State.hpp"
#include "Snake.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"

class Graphics {
	static State *state_;
	static Snake *sn_;
	static Wall *wl_;
	static Fruit *fr_;
public:
	static void SetOpenGLContext(State *s, Snake *sn, Wall *w, Fruit *f, int &argc, char **argv);
	static void SetOpenGLFunctions();
	static void StartGraphics();
private:
	static void renderBitmapString(float x, float y, void *font, const char *string);
	static void DrawObject(int x, int y, GLuint id, double degree);

	static void Display();
	static void Timer(int);
	static void Keyboard(unsigned char key, int x, int y);
	static void Arrow_Keys(int key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void Reshape(int new_width, int new_height);
};
