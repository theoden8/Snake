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
	Aimer *aimer;
	const Snake *snake;
public:
	int
		route = 0,
		strategy = 2;
	const static int NO_ROUTES;

public:
	Router(Aimer *a);
	const char *GetName() const;
	void SetStep(const Ball &target, Ball &step) const;
private:
	void SetStepStraight(const Ball &target, Ball &step) const;
	void SetStepShortest(const Ball &target, Ball &step) const;
	void SetStepsSpaciest(const Ball &target, Ball &step) const;
};
