#pragma once

#include <map>
#include <string>

struct Router {
	std::map <int, std::string> name;
	int mode;

       	Ball &target;
	Ball &from;

       	int &strategy;
	int range;

	std::map <Ball, bool> &sonar;

	Snakes *s;
	Walls *c;

	Router ();

	Ball GetPointStraight();
	Ball GetPointShortest();
	Ball GetStepsSpaciest();
};
