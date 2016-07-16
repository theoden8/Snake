#include "Router.hpp"
#include "Functions.hpp"
#include "Graphics.hpp"
#include "State.hpp"
#include "Snake.hpp"
#include "Aimer.hpp"

#include <iostream>

const int Router::NO_ROUTES = 4;

Router::Router(Aimer *a):
	aimer(a), snake(a->GetSnake())
{}

const char *Router::GetName() const {
	switch(route) {
		case 0:
			return "Human";
		case 1:
			return "Fatalist";
		case 2:
			if(strategy == 1)
				return "Horizontal Shooter";
			else if(strategy == 1e9)
				return "Vertical Shooter";
			return "Random Shooter";
		case 3:
			return "Tracker";
		case 4:
			return "Sir Robin";
		default:
			return NULL;
	}
}

void Router::SetStep(const Ball &from, const Ball &target, Ball &step) const {
	std::cout << "router:  from " << from << " to  target " << target << std::endl;
	switch(route) {
		case 0:
			step = snake->currentDirection;
		break;
		case 1:
		case 2:
			SetStepStraight(from, target, step);
			std::cout << "returned " << step << std::endl;
		break;
		case 3:
			SetStepShortest(from, target, step);
		break;
		case 4:
			SetStepsSpaciest(from, target, step);
		break;
	}
	std::cout << "router step " << step << std::endl;
}


/*
 * Does not care about any obstacles, goes straight to the target.
 */
void Router::SetStepStraight(const Ball &from, const Ball &target, Ball &step) const {
	step = target - from;

	step = Ball(
		(step.x != 0) ? step.x / abs(step.x) : 0,
		(step.y != 0) ? step.y / abs(step.y) : 0
	);
	std::cout << "step_straight " << step << std::endl;

	if(step.x != 0 && step.y != 0) {
		if(
			Ball::InSegment(from + Ball(step.x, 0), WALLS->GetObjects())
			|| Ball::InSegment(from + Ball(step.x, 0), snake->GetObjects())
			|| rand() % strategy
		)
			step.x = 0;
		else
			step.y = 0;
	}
	std::cout << "step_straight " << step << std::endl;

	if(from + step == snake->GetObjects()[1]) {
		if(rand() & 1) {
			step.x = !step.x;
			step.y = !step.y;
		}
		step.x *= (rand() & 1) ? -1 : 1;
		step.y *= (rand() & 1) ? -1 : 1;
	}
}

void Router::SetStepShortest(const Ball &from, const Ball &target, Ball &step) const {
	std::map <Ball, int> way_to = bfs(aimer->GetSonar(), target);
	for(const auto &st : GetSteps()) {
		Ball move(from + st);
		if(way_to.count(move) == 1
			&& way_to[move] + 1 == range)
		{
			step = st;
			return;
		}
	}
}

void Router::SetStepsSpaciest(const Ball &from, const Ball &target, Ball &step) const {
	int space = 0;
	std::vector <Ball> steps;
	for(const auto &step : GetSteps()) {
		Ball move(from + step);
		if(!aimer->GetSonar().count(move)) {
			std::map <Ball, int> way_to = bfs(aimer->GetSonar(), move);
			if(space <= way_to.size()) {
				if(space < way_to.size()) {
					space = way_to.size();
					steps = {};
				} else {
					steps.push_back(step);
				}
			}
		}
	}
	step = steps.front();
}
