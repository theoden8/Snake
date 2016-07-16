#include <cstdlib>

#include "Common.hpp"
#include "Snake.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"

Object
	*WALLS = NULL,
	*FRUITS = NULL,
	*SNAKE = NULL;

void Common::Init(const int argc, char **argv) {
	SNAKE = new Snake();
	WALLS = new Wall();
	FRUITS = new Fruit((argc == 4) ? atoi(argv[3]) : 2);
}

void Common::Keyboard(char key) {
}

void Common::Display() {
}
