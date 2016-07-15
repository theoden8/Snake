#pragma once

#include <map>
#include <string>

#include "Ball.hpp"

#define INVALID_INT -1

class Aimer;
class Snake;

class Router {
	int
		range = INVALID_INT;
	const Snake *snake;
public:
	int
		mode = 0,
		strategy = 2;
	std::map <Ball, bool> &sonar;

public:
	Router(Aimer *a);
	const char *GetName() const;
	void SetPoint(const Ball &from, const Ball &target, Ball &point) const;
private:
	void SetPointStraight(const Ball &from, const Ball &target, Ball &point) const;
	void SetPointShortest(const Ball &from, const Ball &target, Ball &point) const;
	void SetStepsSpaciest(const Ball &from, const Ball &target, Ball &point) const;
};
