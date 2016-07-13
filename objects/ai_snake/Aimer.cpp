#include "Aimer.hpp"
#include "Functions.hpp"
#include "Graphics.hpp"
#include "State.hpp"
#include "Snake.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"

#define state Graphics::state

const char *Aimer::GetName(int aim) {
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

void Aimer::SetTarget(Ball &target, int aim) {
	for(auto obst : {WALLS->walls, SNAKE->snake})
		AddObstacle(obst);

	DeleteSnakeObstacles();
	sonar.erase(SNAKE->snake.back());
	range = INVALID_INT;
	way_to = bfs(sonar, SNAKE->snake.front());
	switch(aim) {
		case 0:
		break;
		case 1:
			SetTargetClosest(target);
		break;
		case 2:
			SetTargetNewest(target);
		break;
		case 3:
			SetTargetFurthest(target);
		break;
		case 4:
			SetTargetSnakeTail(target);
		break;
		default:
			return;
	}
}

void Aimer::AddObstacle(std::vector <Ball> &objects) {
	for(const auto &ball : objects)
		sonar[ball] = true;
}

void Aimer::DeleteSnakeObstacles() {
	Ball &from = SNAKE->snake.front();
	std::map <Ball, int> way_to = bfs(sonar, from);
	for(int i = 1; i < SNAKE->snake.size(); ++i) {
		if(way_to[SNAKE->snake[i]] > SNAKE->snake.size() - i)
			sonar.erase(SNAKE->snake[i]);
	}
}

void Aimer::SetTargetFurthest(Ball &target) {
	for(const auto &f : FRUITS->fruitStorage) {
		if(way_to.count(f))
			if(
				range == INVALID_INT
				|| range > way_to[f]
			)
			{
				target = f;
				range = way_to[target];
			}
	}
}

void Aimer::SetTargetClosest(Ball &target) {
	for(const auto &f : FRUITS->fruitStorage) {
		if(way_to.count(f)) {
			if(range < way_to[f]) {
				target = f;
				range = way_to[target];
			}
		}
	}
}

void Aimer::SetTargetNewest(Ball &target) {
	range = way_to[target];
}

void Aimer::SetTargetSnakeTail(Ball &target) {
	target = SNAKE->snake.back();
	for(int i = SNAKE->snake.size() - 1; i >= 0; --i) {
		if(way_to.count(target)) {
			target = SNAKE->snake[i];
			range = way_to[target];
			return;
		}
	}
}
