#include <math.h>
#include <cstdlib>
#include <iostream>

#include "Snake.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"
#include "Functions.hpp"

Snake::Snake(std::string folder, int X, int Y, Aimer &a, Router &r):
	snake({Ball(X >> 1, Y >> 1)}), aimer(a), router(r)
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
		break;
	}
	if(strchr("wasd", key)) {
		Ball move;
		switch(key) {
			case 'a':
				move = Ball(-1, 0);
			break;
			case 'w':
				move = Ball(0, 1);
			break;
			case 's':
				move = Ball(0, -1);
			break;
			case 'd':
				move = Ball(1, 0);
			break;
		}
		sn_->AutoCorrection(move, wls_, fr_);
	}
	if(strchr("01234", key)) {
		num = key - '0';
		++ID %= 8;
		if(mode != num) {
			aim = 1;
			mode = num;
		} else {
			++aim %= 5;
		}
		if(key == '2') {
			strategy = (rand() & 1) ? 1 : 1e9;
		} else if(key == '5') {
//				s->mode = 7;
//				if(!latency_delta)
//					latency = 0;
		}
	}
}

void Snake::AutoCorrection(Ball point, Wall *w, Fruit *f) {
	if(
		sonar[snake.front() + point]
	   && safe
	)
	{
		std::map <Ball, bool> sonar;
		AddObstacle(sonar, w->walls);
		AddObstacle(sonar, snake);
		AutoCD_C(w, f);
	} else {
		SetStep(point);
	}
}

void Snake::Auto(Wall *w, Fruit *f) {
	Ball
		target,
		point;
	aimer.SetTarget(target, aim);
	router.SetPoint(point, target, mode);
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
	for(const auto &it_step : GetSteps()) {
		Ball movv = snake.front() + it_step.second;
		if(sonar.count(movv) == 0) {
			std::map <Ball, int> way_to = bfs(sonar, movv);
			int NEW_MAX = way_to.size();
			if(NEW_MAX >= MAX) {
				if(NEW_MAX > MAX) {
					FRUIT = 1e9;
					point = it_step.second;
				}
				MAX = NEW_MAX;
				for(const auto &it_fruit : f->fruit_Storage) {
					if(way_to.count(it_fruit) > 0) {
						int NEW_FRUIT = way_to[it_fruit];
						if(NEW_FRUIT < FRUIT) {
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
		if(way_to[snake[i]] > snake.size() - i)
			sonar.erase(snake[i]);
	}
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
				} else
					steps.push_back(step.second);
			}
		}
	}
	return steps;
}

void Snake::SetStep(Ball &point) {
	if(point == -previousDirection)
		return;

	currentDirection = point;
}

void Snake::DoStep() {
	for(int i = snake.size() - 1; i != 0; --i) {
		snake[i] = snake[i - 1];
	}

	snake[0] += currentDirection;
	if(growNextMove) {
		snake.push_back(snakeLast);
		growNextMove = false;
	}
	previousDirection = currentDirection;
}

void Snake::Push_Back() {
	snakeLast = snake.back();
	growNextMove = true;
}
