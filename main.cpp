#include "glut_config.h"
#include "opengl_config.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <string>

#include "Wall.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"
#include "State.hpp"
#include "Aimer.hpp"

#include "Graphics.hpp"

static State *create_state(const int &argc, char **argv) {
	Ball *size = new Ball((argc >= 3) ? Ball(atoi(argv[1]), atoi(argv[2])) : Ball(50, 50));
	State *state = new State(40, size->x, size->y);
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

	Snake *snake;
	Wall *walls;
	Fruit *fruits;
	Aimer aimer(snake, walls, fruits);
	Router router(snake, walls);

	snake = new Snake(state->folder, state->width, state->height, aimer, router);
	walls = new Wall(state->folder, state->width, state->height);
	fruits = create_fruits(argc, argv, state, walls, snake);

	state->walls = walls;
	state->fruits = fruits;
	state->snake = snake;

	Graphics::SetOpenGLContext(
		state,
		snake, walls, fruits,
		argc, argv
	);
	Graphics::SetOpenGLFunctions();

	delete snake; delete walls; delete fruits; delete state;
}
