#include "glut_config.h"
#include "opengl_config.h"

#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Ball.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"
#include "State.hpp"
#include "Aimer.hpp"

#include "Graphics.hpp"

static State *create_state(const int &argc, char **argv) {
	Ball *size = new Ball((argc >= 3) ? Ball(atoi(argv[1]), atoi(argv[2])) : Ball(50, 50));
	State *state = new State(40, 1, size->x, size->y);
	delete(size);
	std::string exec = argv[0];
	state->folder = exec.substr(0, exec.length() - 5);

	state->x_Display = state->width * 1.4;
	state->y_Display = state->height + 0.5;

	return state;
}

static Fruit *create_fruits(const int &argc, char **argv, State *state, Wall *walls, Snake *snake) {
	Fruit *fruit = new Fruit(state->folder, state->width, state->height, 2);
	fruit->Push_Back(walls, snake, 2);
	if(argc == 4)
		fruit->Push_Back(walls, snake, atoi(argv[3]));
	return fruit;
}

int main(int argc, char **argv) {
	srand(time(NULL));

	State *state = create_state(argc, argv);

	Snake *s = new Snake(state->folder, state->width, state->height);
	Wall *w = new Wall(state->folder, state->width, state->height);
	Fruit *f = create_fruits(argc, argv, state, w, s);

	Graphics::SetOpenGLContext(state, s, w, f, argc, argv);
	Graphics::SetOpenGLFunctions();

	Aimer *aimer = new Aimer(s, w, f);

	delete s; delete w; delete f; delete aimer; delete state;

	return 0;
}
