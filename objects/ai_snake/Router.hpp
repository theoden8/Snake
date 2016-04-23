#pragma once

#include <map>
#include <string>

#include "Snake.hpp"
#include "Wall.hpp"
#include "Aimer.hpp"
#include "Functions.hpp"

#define INVALID_INT -1

struct Snake;
struct Aimer;

// gives the step to the aim
struct Router {
	int strategy,
		range = INVALID_INT;
	std::map <Ball, bool> &sonar;
	Snake *s;
	Wall *w;

	Router(Snake *s, Wall *w);

	static char *GetName(int mode, int strategy);
	void SetPoint(Ball &point, Ball &target, int mode);
private:
	void SetPointStraight(Ball &target, Ball &point);
	void SetPointShortest(Ball &target, Ball &point);
	void SetStepsSpaciest(Ball &target, Ball &point);
};
