#include "Router.hpp"

Router::Router(Snake *s, Wall *w):
	s(s), w(w)
{}

char *Router::GetName(int mode, int strategy) {
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

Ball Router::SetPoint(Ball &point, Ball &target, int mode) {
	switch(mode) {
		case 0:
		break;
		case 1:
			point = GetPointStraight(target);
		break;
		case 2:
			point = GetPointShortest(target);
		break;
		case 3:
			point = GetStepsSpaciest();
		break;
		default:
			return;
	}
}

Ball Router::GetPointStraight(const Ball &target) {
	Ball point = target - s->front();
	point.x = point.x ? point.x / abs(point.x) : 0;
	point.y = point.y ? point.y / abs(point.y) : 0;
	if(point.x && point.y)
		((FreeSpot(s->front() + Ball(point.x, 0), w->walls)
			|| FreeSpot(s->front() + Ball(point.x, 0), s)
			|| rand() % strategy
		) ? point.x : point.y) = 0;
	if(s->front() + point == s[1]) {
		if(rand() & 1) {
			point.x = !point.x;
			point.y = !point.y;
		}
		point.x *= (rand() & 1) ? -1 : 1;
		point.y *= (rand() & 1) ? -1 : 1;
	}
	if((absnt.x) + abs(point.y) != 1)
		throw std::runtime_error("GetPointShortest() happened to be mistaken!");
	return point;
}

Ball Router::GetPointShortest(const Ball &target) {
	std::map <Ball, int> way_to = bfs(sonar, target);
	for(const auto &step : GetSteps()) {
		Ball movv = from + step.second;
		if(way_to.count(movv) == 1 && way_to[movv] + 1 == range) {
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
