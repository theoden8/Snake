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
	controller(0),
	X(X), Y(Y),
//Ball
	varDirection(0, -1),
	varPreviousDirection(0, 0),
//bool
	varGrowNextMove(0),
	safe(0)
{
	Crossed.load(folder + "_textures/Cross.tga");
	for(int i = 0; i < 8; ++i) {
		head[i].load(folder + "_textures/" + std::to_string(i) + "_HEAD.tga");
		body[i].load(folder + "_textures/" + std::to_string(i) + "_BODY.tga");
		tail[i].load(folder + "_textures/" + std::to_string(i) + "_TAIL.tga");
	}
	ModeName[0] = "Human";
	ModeName[1] = "Fatalist";
	ModeName[2] = "General";
	ModeName[3] = "Tracker";
	ModeName[4] = "Sir Robin";
	AimName[0] = "Hand Brake";
	AimName[1] = "Closest fruit";
	AimName[2] = "Newest fruit";
	AimName[3] = "Furthest fruit";
	AimName[4] = "Tail";
}

void Snake::Keyboard(char key) {
	switch(key) {
		case 'g' :
			safe = !safe;
		case 'z' :
			controller += 1 - ((controller & 1) << 1);
			break;
		case 'x' :
			controller += (1 - ((controller & 2) << 1)) << 1;
			break;
		case 'c' :
			controller += (1 - ((controller & 4) << 1)) << 2;
			break;
	} if(process_key("01234", key)) {
		++ID %= 8;
		if(mode != key - '0') {
			aim = 1;
			mode = key - '0';
		} else {
			++aim %= aimN;
		}
		if(key == '2') {
				if(rand() & 1) {
					strategy = 1;
					ModeName[mode] = "General Horizon";
				} else {
					strategy = 1e9;
					ModeName[mode] = "General Vertix";
				}
		} else if (key == '5') {
//				s->mode = 7;
//				if(!latency_delta) {
//					latency = 0;
//				}
//				ModeName = "Tornado";
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
	int range = -1;
	switch(aim) {
		case 0:
			return;
		case 1:
			target = GetClosestFruit(f, range, sonar, snake.front());
			break;
		case 2:
			target = GetNewestFruit(f, range, sonar, snake.front());
			break;
		case 3:
			target = GetFurthestFruit(f, range, sonar, snake.front());
			break;
		case 4:
			std::vector <Ball> spacy_steps = GetStepsSpaciest(sonar, snake.front());
			std::vector <Ball> moves;
			for(auto step : GetSteps()) {
				moves.push_back(step.second);
				for(auto sp_step : spacy_steps) {
					if(sp_step == step.second) {
						moves.pop_back();
						break;
					}
				}
			}
//			for(auto mov : moves) {
//				sonar[mov + snake.front()] = 1;
//			}
			target = GetClosestFruit(f, range, sonar, snake.front());
			break;
//		case 5:
//			target = GetSnakeTail(range, sonar, snake.front());
			break;
	}
	switch(mode) {
		case 3:
			point = GetPointShortest(range, sonar, snake.front(), target);
			break;
		case 4:
			point = GetPointShortest(range, sonar, snake.front(), target);
			break;
		default:
			point = GetPointStraight(w, target, strategy);
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
	Ball point = varDirection;
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
	return varDirection;
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
	if(point == -varPreviousDirection) {
		return;
	}
	varDirection = point;
}

void Snake::DoStep() {
	for(int i = snake.size() - 1; i; --i) {
		snake[i] = snake[i - 1];
	}
	snake[0] = snake[0] + varDirection;
	if(varGrowNextMove) {
		snake.push_back(varSnakeLast);
		varGrowNextMove = 0;
	}
	varPreviousDirection = varDirection;
}

void Snake::Push_Back() {
	varSnakeLast = snake.back();
	varGrowNextMove = 1;
}
