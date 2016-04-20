#include "Router.hpp"

Router::Router(Aimer a):
	from(aimer.from), target(aimer.target)
{}

char *Router::GetName(int mode, int strategy) {
	switch(mode) {
		case 0:
			return "Human";
		case 1:
			return "Fatalist";
		case 2:
			if(strategy == 1)
				return "General Horizon";
			else if(strategy == 1e9)
				return "General Vertical";
			return "General";
		case 3:
			return "Tracker";
		case 4:
			return "Sir Robin";
		default:
			return NULL;
	}
}

Ball Router::GetPoint(int mode) {
	switch(mode) {
		case 1:
			return GetPointStraight();
		case 2:
			return GetPointShortest();
		case 3:
			return GetStepsSpaciest();
		default:
			return s->snake.front();
	}
}

Ball Router::GetPointStraight() {
	Ball point = target - s->front();
	point.x = point.x ? point.x / abs(point.x) : 0;
	point.y = point.y ? point.y / abs(point.y) : 0;
	if (point.x && point.y) {
		if(
			FreeSpot(s->front() + Ball(point.x, 0), w->walls)
			|| FreeSpot(s->front() + Ball(point.x, 0), s)
			|| rand() % strategy
		) {
			point.x = 0;
		} else {
			point.y = 0;
		}
	}
	if(s->front() + point == s[1]) {
		if(rand() & 1) {
			point.x = !point.x;
			point.y = !point.y;
		}
		point.x = (rand() & 1) ? -point.x : point.x;
		point.y = (rand() & 1) ? -point.y : point.y;
	}
	if(absnt.x) + abs(point.y) != 1)
		throw std::runtime_error("ALARM! GetPointShortest() happened to be mistaken!");
	return point;
}

Ball Router::GetPointShortest() {
	std::map <Ball, int> way_to = bfs(sonar, target);
	for (const auto &step : GetSteps()) {
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
	for(const auto &step : GetSteps()) {
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
