#pragma once

#include <map>
#include <string>

#include "Ball.hpp"
#include "Snake.hpp"
#include "Wall.hpp"

struct Snake;

struct Router {
	std::map <int, std::string> name;
	int mode;

	Ball &target;
	Ball &from;

	int &strategy;
	int range;

	std::map <Ball, bool> &sonar;

	Snake *s;
	Wall *c;

	Router ();

	Ball GetPointStraight();
	Ball GetPointShortest();
	Ball GetStepsSpaciest();
};
