#include <cstdlib>

#include "Router.hpp"
#include "Functions.hpp"
#include "Graphics.hpp"
#include "State.hpp"
#include "Snake.hpp"

void Router::SetPointStraight(const Ball &from, const Ball &target, Ball &point) const {
	point = target - from;

	point.x = (point.x) ? point.x / abs(point.x) : 0;
	point.y = (point.y) ? point.y / abs(point.y) : 0;

	if(point.x && point.y)
		((Ball::FreeSpot(SNAKE->GetObjects().front() + Ball(point.x, 0), WALLS->GetObjects())
			|| Ball::FreeSpot(SNAKE->GetObjects().front() + Ball(point.x, 0), SNAKE->GetObjects())
			|| rand() % strategy
		) ? point.x : point.y) = 0;

	if(SNAKE->GetObjects().front() + point == SNAKE->GetObjects()[1]) {
		if(rand() & 1) {
			point.x = !point.x;
			point.y = !point.y;
		}
		point.x *= (rand() & 1) ? -1 : 1;
		point.y *= (rand() & 1) ? -1 : 1;
	}

	if(abs(point.x) + abs(point.y) != 1)
		throw std::runtime_error("SetPointShortest happened to be mistaken!");
}

void Router::SetPointShortest(const Ball &from, const Ball &target, Ball &point) const {
	std::map <Ball, int> way_to = bfs(sonar, target);
	for(const auto &step : GetSteps()) {
		Ball move(from + step);
		if(way_to.count(move) == 1 && way_to[move] + 1 == range) {
			point = step;
			return;
		}
	}
	SetPointStraight(from, target, point);
}

void Router::SetStepsSpaciest(const Ball &from, const Ball &target, Ball &point) const {
	int space = 0;
	std::vector <Ball> steps;
	for(const auto &step : GetSteps()) {
		Ball move(from + step);
		if(!sonar.count(move)) {
			std::map <Ball, int> way_to = bfs(sonar, move);
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
	point = steps.front();
}
