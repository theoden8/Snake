#include <math.h>
#include <cstdlib>
#include <iostream>

#include "Snake.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"
#include "Functions.hpp"

Snake::Snake(std::string folder, int X, int Y):
	snake(1, Ball(X >> 1, Y >> 1)),
//int
	ID(0), mode(0), aim(0),
	modeN(5), aimN(5),
	strategy(2),
//Ball
	currentDirection(0, -1),
	previousDirection(0, 0),
//bool
	growNextMove(0),
	safe(0)
{
	Crossed.load(folder + "_textures/Cross.tga");
	for(int i = 0; i < 8; ++i) {
		skins[i].head.load(folder + "_textures/" + std::to_string(i) + "_HEAD.tga");
		skins[i].body.load(folder + "_textures/" + std::to_string(i) + "_BODY.tga");
		skins[i].tail.load(folder + "_textures/" + std::to_string(i) + "_TAIL.tga");
	}
}

void Snake::Keyboard(char key) {
	switch(key) {
		case 'g' :
			safe = !safe;
	}
	if(process_key("01234", key)) {
		++ID %= 8;
		if(mode != key - '0') {
			aim = 1;
			mode = key - '0';
		} else {
			++aim %= aimN;
		}
		if(key == '2') {
				if(rand() & 1)
					strategy = 1;
				else
					strategy = 1e9;
		} else if (key == '5') {
//				s->mode = 7;
//				if(!latency_delta)
//					latency = 0;
		}
	}
}

void Snake::AutoCorrection(Ball point, Wall *w, Fruit *f) {
	std::map <Ball, bool> sonar;
		AddObstacle(sonar, w->walls);
		AddObstacle(sonar, snake);
	if(sonar[snake.front() + point] && safe) {
		AutoCD_C(w, f);
	} else {
		SetStep(point);
	}
}

void Snake::ArtificialMove(Wall *w, Fruit *f) {
	Ball target,
		 point;
	std::map <Ball, bool> sonar;
		AddObstacle(sonar, w->walls);
		AddObstacle(sonar, snake);
		DeleteSnakeObstacles(sonar, snake.front());
	switch(aim) {
		case 0:
			return;
		case 1: case 2: case 3:
			target = aimer.GetTarget(aim);
			break;
	}
	switch(mode) {
		case 0:
			break;
		case 1: case 2: case 3: case 4:
			point = router.GetPoint(mode, strategy);
			break;
	}
	AutoCorrection(point, w, f);
}

//C	Sir Robin
void Snake::AutoCD_C (Wall *w, Fruit *f) {
	std::map <Ball, bool> sonar;
		AddObstacle(sonar, w->walls);
		AddObstacle(sonar, snake);
		DeleteSnakeObstacles(sonar, snake.front());
	int MAX = 0, FRUIT = 1e9;
	Ball point = currentDirection;
	for (auto it_step : GetSteps()) {
		Ball movv = snake.front() + it_step.second;
		if (sonar.count(movv) == 0) {
			std::map <Ball, int> way_to = bfs(sonar, movv);
			int NEW_MAX = way_to.size();
			if (NEW_MAX >= MAX) {
				if (NEW_MAX > MAX) {
					FRUIT = 1e9;
					point = it_step.second;
				}
				MAX = NEW_MAX;
				for (auto it_fruit : f->fruit_Storage) {
					if (way_to.count(it_fruit) > 0) {
						int NEW_FRUIT = way_to[it_fruit];
						if (NEW_FRUIT < FRUIT) {
							FRUIT = NEW_FRUIT;
							point = it_step.second;
						}
					}
				}
			}
		}
	}
	SetStep(point);
}

void Snake::AddObstacle(std::map <Ball, bool> &sonar, std::vector <Ball> &objects) {
	for(auto ball : objects) {
		sonar[ball] = true;
	}
}

void Snake::DeleteSnakeObstacles(std::map <Ball, bool> &sonar, Ball &from) {
	std::map <Ball, int> way_to = bfs(sonar, from);
	for(int i = 1; i < snake.size(); ++i) {
		if(way_to[snake[i]] > snake.size() - i) {
			sonar.erase(snake[i]);
		}
	}
}


Ball Snake::GetClosestFruit(Fruit *f, int &range, std::map <Ball, bool> &sonar, Ball &from) {
	std::map <Ball, int> way_to = bfs(sonar, from);
	Ball target = f->fruit_Storage.front();
	for(auto it_fruit : f->fruit_Storage) {
		if (way_to.count(it_fruit)) {
			if (
				range == -1
				|| range > way_to[it_fruit]
			) {
				target = it_fruit;
				range = way_to[target];
			}
		}
	}
	return target;
}

Ball Snake::GetNewestFruit(Fruit *f, int &range, std::map <Ball, bool> &sonar, Ball &from) {
	Ball target = f->fruit_Storage.front();
	if(
		mode != 1 &&
		mode != 2
	) {
		std::map <Ball, int> way_to = bfs(sonar, from);
		range = way_to[target];
	}
	return target;
}

Ball Snake::GetFurthestFruit(Fruit *f, int &range, std::map <Ball, bool> &sonar, Ball &from) {
	std::map <Ball, int> way_to = bfs(sonar, from);
	Ball target = f->fruit_Storage.front();
	for(auto it_fruit : f->fruit_Storage) {
		if (way_to.count(it_fruit)) {
			if (range < way_to[it_fruit]) {
				target = it_fruit;
				range = way_to[target];
			}
		}
	}
	return target;
}

Ball Snake::GetSnakeTail (int &range, std::map <Ball, bool> &sonar, Ball &from) {
	sonar.erase(snake.back());
	Ball target = snake.back();
	std::map <Ball, int> way_to = bfs(sonar, from);
	for(int i = snake.size() - 1; i >= 0; --i) {
		if(way_to.count(target)) {
			target = snake[i];
			range = way_to[target];
			return target;
		}
	}
	return target;
}

Ball Snake::GetPointStraight(Wall *w, Ball &target, int &strategy) {
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

Ball Snake::GetPointShortest(int range, std::map <Ball, bool> &sonar, Ball &from, Ball &target) {
	std::map <Ball, int> way_to = bfs(sonar, target);
	for (auto step : GetSteps()) {
		Ball movv = from + step.second;
		if (way_to.count(movv) == 1 && way_to[movv] + 1 == range) {
			return step.second;
		}
	}
	return currentDirection;
}

std::vector <Ball> Snake::GetStepsSpaciest(std::map <Ball, bool> &sonar, Ball &from) {
	int space(0);
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
	return steps;
}

void Snake::SetStep (Ball &point) {
	if(point == -previousDirection) {
		return;
	}
	currentDirection = point;
}

void Snake::DoStep() {
	for(int i = snake.size() - 1; i; --i) {
		snake[i] = snake[i - 1];
	}
	snake[0] = snake[0] + currentDirection;
	if(growNextMove) {
		snake.push_back(snakeLast);
		growNextMove = 0;
	}
	previousDirection = currentDirection;
}

void Snake::Push_Back() {
	snakeLast = snake.back();
	growNextMove = 1;
}
