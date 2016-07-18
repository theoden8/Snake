#pragma once

#include <map>

#include "Ball.hpp"

class Aimer;
class Snake;

class Router {
	Aimer *aimer;
	const Snake *snake;
public:
	int
		strategy = 2,
		route = 0;
	const static int NO_ROUTES;

public:
	Router(Aimer *a);
	const char *Name() const;
	void SetStrategy(int strat);

	Ball GetStep() const;

private:
	Ball GetStepHeuristically() const;
	Ball GetStepShortestRoute() const;
	Ball GetStepShortestRoute(const std::vector <Ball> &steps) const;
	Ball GetStepSpaciestRoute() const;
};
