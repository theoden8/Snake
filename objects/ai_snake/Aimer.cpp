#include "Aimer.hpp"

Aimer::Aimer(Snake *s, Wall *s):
	s(s), w(w)
{}

void Aimer::AddObstacle(std::vector <Ball> &objects) {
	for(const auto &ball : objects)
		sonar[ball] = true;
}

void Aimer::DeleteSnakeObstacles() {
	std::map <Ball, int> way_to = bfs(sonar, from);
	for(int i = 1; i < s->snake.size(); ++i)
		if(way_to[s->snake[i]] > s->snake.size() - i)
			sonar.erase(s->snake[i]);
}

void Aimer::Initialize() {
	AddObstacle(w->walls);
	AddObstacle(s->snake);
	from = s->snake.front();
	DeleteSnakeObstacles();
	sonar.erase(s->snake.back());
	range = -1;
	way_to = bfs(sonar, from);
	target = f->fruit_Storage.front();
}

Ball Aimer::GetTargetFurthest() {
	Initialize();
	for(const auto &f : f->fruit_Storage) {
		if(way_to.count(f)) {
			if(
				range == -1
				|| range > way_to[f]
			) {
				target = f;
				range = way_to[target];
			}
		}
	}
	return target;
}

Ball Aimer::GetTargetClosest() {
	Initialize();
	for(const auto &f : f->fruit_Storage) {
		if(way_to.count(f)) {
			if(range < way_to[f]) {
				target = f;
				range = way_to[target];
			}
		}
	}
	return target;
}

Ball Aimer::GetTargetNewest() {
	Initialize();
	range = way_to[target];
	return target;
}

Ball Aimer::GetSnakeTail() {
	Initialize();
	target = s->snake.back();
	for(int i = s->snake.size() - 1; i >= 0; --i) {
		if(way_to.count(target)) {
			target = s->snake[i];
			range = way_to[target];
			return target;
		}
	}
	return target;
}
