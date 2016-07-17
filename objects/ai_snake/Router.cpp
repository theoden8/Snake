#include "Router.hpp"
#include "Functions.hpp"
#include "Graphics.hpp"
#include "State.hpp"
#include "Snake.hpp"
#include "Aimer.hpp"

#include <cassert>
#include <iostream>

const int Router::NO_ROUTES = 4;

Router::Router(Aimer *a):
	aimer(a), snake(a->GetSnake())
{}

const char *Router::GetName() const {
	switch(route) {
		case 0:
			return "Manual";
		case 1:
		case 2:
			if(strategy == 1)
				return "Heuristics (Horizontal)";
			else if(strategy == 1e9)
				return "Heuristics (Vertical)";
			return "Heuristics (Random)";
		case 3:
			return "Path Finder";
		case 4:
			return "Underground";
		default:
			return NULL;
	}
}

Ball Router::GetStep(const Ball &target) const {
	Ball step;

	assert(target.is_valid_position());

	switch(route) {
		case 0:
			step = snake->currentDirection;
		break;
		case 1:
		case 2:
			SetStepHeuristically(target, step);
		break;
		case 3:
			SetStepShortestRoute(target, step);
			if(!step.is_valid_step())
				step = snake->currentDirection;
		break;
		case 4:
			SetStepSpaciestRoute(target, step);
			if(!step.is_valid_step())
				step = snake->currentDirection;
		break;
	}
	std::cout << "router step " << step << std::endl;

	assert(step.is_valid_step());
	return step;
}


void Router::SetStepHeuristically(const Ball &target, Ball &step) const {
	const Ball &from = snake->head();
	step = target - from;

	step = Ball(
		(step.x != 0) ? step.x / abs(step.x) : 0,
		(step.y != 0) ? step.y / abs(step.y) : 0
	);

	if(step.x != 0 && step.y != 0) {
		if(
			Ball::InSegment(from + Ball(step.x, 0), WALLS->GetObjects())
			|| Ball::InSegment(from + Ball(step.x, 0), snake->GetObjects())
		)
		{
			step.x = 0;
		}
		if(
			Ball::InSegment(from + Ball(step.y, 0), WALLS->GetObjects())
			|| Ball::InSegment(from + Ball(step.y, 0), snake->GetObjects())
		)
		{
			step.y = 0;
		}

		if(step.x != 0 && step.y != 0) {
			((rand() % strategy) ? step.x : step.y) = 0;
		} else
		if(step == Ball(0, 0)) {
			step = snake->currentDirection;
			return;
		}
	}

	if(from + step == snake->GetObjects()[1]) {
		step.x = !step.x;
		step.y = !step.y;
		if(rand() & 1)
			step.x = -step.x;
		if(rand() & 1)
			step.y = -step.y;
	}
}

void Router::SetStepShortestRoute(const Ball &target, Ball &step) const {
	const Ball &from = snake->head();
	std::map <Ball, int> way_to = bfs(aimer->GetSonar(), target);
	for(const auto &st : GetSteps()) {
		Ball move(from + st);
		if(
			way_to.count(move) == 1
			&& way_to[move] == aimer->range - 1
		) {
			std::cout << "step = " << st << std::endl;
			step = st;
			return;
		}
	}
	std::cout << "shortest" << step << std::endl;
}

void Router::SetStepSpaciestRoute(const Ball &target, Ball &step) const {
	int space = 0;
	const Ball &from = snake->head();
	std::vector <Ball> steps;
	for(const auto &step : GetSteps()) {
		Ball move(from + step);
		if(!aimer->GetSonar().count(move)) {
			std::map <Ball, int> way_to = bfs(aimer->GetSonar(), move);
			if(space <= way_to.size()) {
				if(space < way_to.size()) {
					space = way_to.size();
					steps.clear();
				} else {
					steps.push_back(step);
				}
			}
		}
	}
	step = steps.front();
}
