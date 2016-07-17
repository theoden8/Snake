#pragma once

#include <map>
#include <string>

#include "Ball.hpp"

class Aimer;
class Snake;

class Router {
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
	Ball GetStep(const Ball &target) const;
private:
	void SetStepHeuristically(const Ball &target, Ball &step) const;
	void SetStepShortestRoute(const Ball &target, Ball &step) const;
	void SetStepSpaciestRoute(const Ball &target, Ball &step) const;
};
