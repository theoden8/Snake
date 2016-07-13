#pragma once

#include <map>
#include <string>

#include "Ball.hpp"

#define INVALID_INT -1

class Router {
public:
	int strategy,
		range = INVALID_INT;
	std::map <Ball, bool> &sonar;

	Router();

	static const char *GetName(int mode, int strategy);
	void SetPoint(const Ball &from, Ball &point, Ball &target, int mode);
private:
	void SetPointStraight(const Ball &from, Ball &target, Ball &point);
	void SetPointShortest(const Ball &from, Ball &target, Ball &point);
	void SetStepsSpaciest(const Ball &from, Ball &target, Ball &point);
};
