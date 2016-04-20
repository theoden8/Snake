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

	int range = -1;

	std::map <Ball, bool> &sonar;

	Snake *s;
	Wall *w;

	Router(Aimer &a);

	static char *GetName(int mode, int strategy);
	Ball GetPoint(int mode);
private:
	Ball GetPointStraight();
	Ball GetPointShortest();
	Ball GetStepsSpaciest();
};
