#include <cstdlib>

#include "State.hpp"
#include "Snake.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"

void State::InitStateFin(const int argc, char **argv) {
	SNAKE = new Snake();
	WALLS = new Wall();
	FRUITS = new Fruit((argc == 4) ? atoi(argv[3]) : 2);
}
