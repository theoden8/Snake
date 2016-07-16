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
		mode = 0,
		strategy = 2;
	const static int NO_MODES;

public:
	Router(Aimer *a);
	const char *GetName() const;
	void SetStep(const Ball &from, const Ball &target, Ball &step) const;
private:
	void SetStepStraight(const Ball &from, const Ball &target, Ball &step) const;
	void SetStepShortest(const Ball &from, const Ball &target, Ball &step) const;
	void SetStepsSpaciest(const Ball &from, const Ball &target, Ball &step) const;
};
