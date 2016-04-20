#include "Aimer.hpp"
#include "Functions.hpp"

const int Aimer::DEFAULT_RANGE = -1;

Aimer::Aimer(Snake *s, Wall *w, Fruit *f):
	s(s), w(w), f(f)
{}

char *Aimer::GetName(int aim) {
	switch(aim) {
		case 0:
			return "Hand Brake";
		case 1:
			return "Closest Fruit";
		case 2:
			return "Newest fruit";
		case 3:
			return "Furthest fruit";
		case 4:
			return "Tail";
		default:
			return NULL;
	}
}

Ball Aimer::GetTarget(int aim) {
	AddObstacle(w->walls);
	AddObstacle(s->snake);
	DeleteSnakeObstacles();
	sonar.erase(s->snake.back());
	range = DEFAULT_RANGE;
	way_to = bfs(sonar, *from);
	*target = f->fruit_Storage.front();
	switch(aim) {
		case 1:
			return GetTargetClosest();
		case 2:
			return GetTargetNewest();
		case 3:
			return GetTargetFurthest();
		case 4:
			return GetSnakeTail();
		default:
			return s->snake.front();
	}
}

void Aimer::AddObstacle(std::vector <Ball> &objects) {
	for(const auto &ball : objects)
		sonar[ball] = true;
}

void Aimer::DeleteSnakeObstacles() {
	*from = s->snake.front();
	std::map <Ball, int> way_to = bfs(sonar, *from);
	for(int i = 1; i < s->snake.size(); ++i)
		if(way_to[s->snake[i]] > s->snake.size() - i)
			sonar.erase(s->snake[i]);
}

Ball Aimer::GetTargetFurthest() {
	for(const auto &f : f->fruit_Storage) {
		if(way_to.count(f)) {
			if(
				range == DEFAULT_RANGE
				|| range > way_to[f]
			) {
				*target = f;
				range = way_to[*target];
			}
		}
	}
	return *target;
}

Ball Aimer::GetTargetClosest() {
	for(const auto &f : f->fruit_Storage) {
		if(way_to.count(f)) {
			if(range < way_to[f]) {
				*target = f;
				range = way_to[*target];
			}
		}
	}
	return *target;
}

Ball Aimer::GetTargetNewest() {
	range = way_to[*target];
	return *target;
}

Ball Aimer::GetSnakeTail() {
	*target = s->snake.back();
	for(int i = s->snake.size() - 1; i >= 0; --i) {
		if(way_to.count(*target)) {
			*target = s->snake[i];
			range = way_to[*target];
			return *target;
		}
	}
	return *target;
}
