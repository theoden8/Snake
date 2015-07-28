#include "Router.hpp"

Router::Router() :
{}

Ball Router::GetPointStraight() {
	Ball point = target - snake.front();
	point.x = point.x ? point.x / abs(point.x) : 0;
	point.y = point.y ? point.y / abs(point.y) : 0;
	if (point.x && point.y) {
		if(
			FreeSpot(snake.front() + Ball(point.x, 0), w->walls)
			|| FreeSpot(snake.front() + Ball(point.x, 0), snake)
			|| rand() % strategy
		) {
			point.x = 0;
		} else {
			point.y = 0;
		}
	}
	if(snake.front() + point == snake[1]) {
		if(rand() & 1) {
			point.x = !point.x;
			point.y = !point.y;
		}
		point.x = (rand() & 1) ? -point.x : point.x;
		point.y = (rand() & 1) ? -point.y : point.y;
	}
	if(abs(point.x) + abs(point.y) != 1)
		throw std::runtime_error("ALARM! GetPointShortest() happened to be mistaken!");
	return point;
}

Ball Router::GetPointShortest() {
	std::map <Ball, int> way_to = bfs(sonar, target);
	for (auto step : GetSteps()) {
		Ball movv = from + step.second;
		if (way_to.count(movv) == 1 && way_to[movv] + 1 == range) {
			return step.second;
		}
	}
	return GetPointStraight();
}

Ball Router::GetStepsSpaciest() {
	int space = 0;
	std::vector <Ball> steps;
	for(auto step : GetSteps()) {
		Ball move = from + step.second;
		if(!sonar.count(move)) {
			std::map <Ball, int> way_to = bfs(sonar, move);
			if(space <= way_to.size()) {
				if(space < way_to.size()) {
					space = way_to.size();
					steps = {};
				} else {
					steps.push_back(step.second);
				}
			}
		}
	}
	return steps.front();
}
