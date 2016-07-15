#include "Router.hpp"
#include "Aimer.hpp"

Router::Router(Aimer *a):
	sonar(a->sonar), snake(a->GetSnake())
{}

void Router::SetPoint(const Ball &from, const Ball &target, Ball &point) const {
	switch(mode) {
		case 0:
		break;
		case 1:
			SetPointStraight(from, target, point);
		break;
		case 2:
			SetPointShortest(from, target, point);
		break;
		case 3:
			SetStepsSpaciest(from, target, point);
		break;
		default:
			return;
	}
}

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
