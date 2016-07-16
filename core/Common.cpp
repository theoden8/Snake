#include <cstdlib>
#include <iostream>

#include "Common.hpp"
#include "State.hpp"
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

void Common::Display() {
}

void Common::Timer() {
	if(!State::pause) {
		if(!State::running)
			SSNAKE->DoStep();
		if(
			Ball::InSegment(SNAKE->GetObjects().front(), WALLS->GetObjects())
			|| Ball::InSegment(SNAKE->GetObjects().front(), SNAKE->GetObjects(), Ball(1, SNAKE->GetObjects().size()))
		)
		{
			std::cout << std::to_string(FFRUITS->frufru) << std::endl;
			exit(0);
		}
	}
	if(Ball::InSegment(SNAKE->GetObjects().front(), FRUITS->GetObjects()))
		FFRUITS->EatFruit();

	SSNAKE->AutomaticMove();
}
