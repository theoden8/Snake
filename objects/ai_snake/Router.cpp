#include <cstdlib>

#include "Router.hpp"
#include "Functions.hpp"
#include "Graphics.hpp"
#include "State.hpp"
#include "Wall.hpp"
#include "Snake.hpp"

const char *Router::GetName(int mode, int strategy) {
	switch(mode) {
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

void Router::SetPoint(const Ball &from, Ball &point, Ball &target, int mode) {
	switch(mode) {
		case 0:
		break;
		case 1:
			SetPointStraight(from, target, point);
		break;
		case 2:
			SetPointShortest(from, target, point);
		break;
		case 3:
			SetStepsSpaciest(from, target, point);
		break;
		default:
			return;
	}
}

void Router::SetPointStraight(const Ball &from, Ball &target, Ball &point) {
	point = target - from;

	point.x = (point.x) ? point.x / abs(point.x) : 0;
	point.y = (point.y) ? point.y / abs(point.y) : 0;

	if(point.x && point.y)
		((Ball::FreeSpot(SNAKE->snake.front() + Ball(point.x, 0), WALLS->walls)
			|| Ball::FreeSpot(SNAKE->snake.front() + Ball(point.x, 0), SNAKE->snake)
			|| rand() % strategy
		) ? point.x : point.y) = 0;

	if(SNAKE->snake.front() + point == SNAKE->snake[1]) {
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

void Router::SetPointShortest(const Ball &from, Ball &target, Ball &point) {
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

void Router::SetStepsSpaciest(const Ball &from, Ball &target, Ball &point) {
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
