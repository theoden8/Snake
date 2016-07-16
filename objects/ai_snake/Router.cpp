#include "Router.hpp"
#include "Aimer.hpp"

const int Router::NO_MODES = 3;

Router::Router(Aimer *a):
	sonar(a->sonar), snake(a->GetSnake())
{}

const char *Router::GetName() const {
	switch(mode) {
		case 0:
			return "Human";
		case 1:
			return "Fatalist";
		case 2:
			if(strategy == 1)
				return "Horizontal Shooter";
			else if(strategy == 1e9)
				return "Vertical Shooter";
			return "Random Shooter";
		case 3:
			return "Tracker";
		case 4:
			return "Sir Robin";
		default:
			return NULL;
	}
}
