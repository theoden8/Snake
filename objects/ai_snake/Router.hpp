#pragma once

#include <map>
#include <string>

#include "Snake.hpp"
#include "Wall.hpp"
#include "Aimer.hpp"

struct Snake;
struct Aimer;

// gives the step to the aim
struct Router {
	std::map <int, std::string> name;
	int strategy;

	Ball &target, &from;

	int range = INVALID_INT;

	std::map <Ball, bool> &sonar;

	Snake *s;
	Wall *w;

	Router(Snake *s, Wall *w);

	static char *GetName(int mode, int strategy);
	Ball GetPoint(int mode);
private:
	Ball GetPointStraight(const Ball &target);
	Ball GetPointShortest(const Ball &target);
	Ball GetStepsSpaciest(const Ball &target);
};
