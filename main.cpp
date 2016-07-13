#include "glut_config.h"
#include "opengl_config.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include <string>


#include "State.hpp"

#include "Graphics.hpp"
class Fruit;
class Wall;
class Snake;
#include "Fruit.hpp"
#include "Wall.hpp"
class Aimer;
class Router;
#include "Snake.hpp"

static Fruit *create_fruits(const int &argc, char **argv) {
	Fruit *fruit = new Fruit(2);
	fruit->Push_Back(2);
	if(argc == 4)
		fruit->Push_Back(atoi(argv[3]));
	return fruit;
}

int main(int argc, char **argv) {
	srand(time(NULL));

	State::InitState(argc, argv);

	SNAKE = new Snake();
	WALLS = new Wall();
	FRUITS = create_fruits(argc, argv);

	Graphics::SetOpenGLContext(argc, argv);
	Graphics::SetOpenGLFunctions();

	delete SNAKE; delete WALLS; delete FRUITS;
}
