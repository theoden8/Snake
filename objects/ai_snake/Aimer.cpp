#include "Aimer.hpp"

const int Aimer::NO_AIMS = 4;

Aimer::Aimer(Snake *s):
	snake(s)
{}

const char *Aimer::GetName() const {
	switch(aim) {
		case 0:
			return "Hand Brake";
		case 1:
			return "Closest Fruit";
		case 2:
			return "Newest fruit";
		case 3:
			return "Furthest fruit";
		case 4:
			return "Tail";
		default:
			return NULL;
	}
}

const Snake *Aimer::GetSnake() const {
	return snake;
}
