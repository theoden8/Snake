#include <math.h>
#include <cstdlib>
#include <iostream>

#include "Graphics.hpp"
#include "Snake.hpp"
#include "Functions.hpp"
#include "Aimer.hpp"
#include "Router.hpp"


Snake::Snake():
	snake({Ball(
		int(State::width) >> 1,
		int(State::height) >> 1
	)})
{
	Crossed.load(State::folder + "_textures/Cross.tga");
	for(int i = 0; i < 8; ++i) {
		skins[i].head.load(State::folder + "_textures/" + std::to_string(i) + "_HEAD.tga");
		skins[i].body.load(State::folder + "_textures/" + std::to_string(i) + "_BODY.tga");
		skins[i].tail.load(State::folder + "_textures/" + std::to_string(i) + "_TAIL.tga");
	}
	aimer = new Aimer();
	router = new Router();
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
		AutoCorrection(move);
	}
	if(strchr("01234", key)) {
		int num = key - '0';
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

void Snake::Display() {
	for(int i = 0; i < snake.size(); ++i) {
		GLuint id;
		double degree = 90;
		if(i == 0) {
			id = skins[ID].head.id;
			degree = currentDirection.degree();
		} else if(i == snake.size() - 1) {
			id = skins[ID].body.id;
			degree = (snake[i - 1] - snake[i]).degree();
		} else {
			id = skins[ID].tail.id;
			degree = (snake[i - 1] - snake[i]).degree();
		}
		Graphics::DrawObject(snake[i].x, snake[i].y, id, degree);
	}
}


void Snake::AutoCorrection(Ball point) {
	/* if( */
	/* 	router.sonar[snake.front() + point] */
	/* 	&& safe */
	/* ) */
	/* { */
	/* 	std::map <Ball, bool> sonar; */
	/* 	AddObstacle(sonar, WALLS->walls); */
	/* 	AddObstacle(sonar, snake); */
	/* 	AutoCD_C(); */
	/* } else { */
	/*	SetStep(point); */
	/* } */
	SetStep(point);
}

void Snake::AutomaticMove() {
	Ball
		target,
		point;
	aimer->SetTarget(target, aim);
	router->SetPoint(snake.front(), point, target, mode);
	AutoCorrection(point);
}

//C	Sir Robin
/* void Snake::AutoCD_C() { */
/* 	std::map <Ball, bool> sonar; */
/* 		AddObstacle(sonar, WALLS->walls); */
/* 		AddObstacle(sonar, snake); */
/* 		DeleteSnakeObstacles(sonar, snake.front()); */
/* 	int MAX = 0, FRUIT = 1e9; */
/* 	Ball point = currentDirection; */
/* 	for(const auto &it_step : GetSteps()) { */
/* 		Ball movv = snake.front() + it_step; */
/* 		if(sonar.count(movv) == 0) { */
/* 			std::map <Ball, int> way_to = bfs(sonar, movv); */
/* 			int NEW_MAX = way_to.size(); */
/* 			if(NEW_MAX >= MAX) { */
/* 				if(NEW_MAX > MAX) { */
/* 					FRUIT = 1e9; */
/* 					point = it_step; */
/* 				} */
/* 				MAX = NEW_MAX; */
/* 				for(const auto &it_fruit : FRUITS->fruitStorage) { */
/* 					if(way_to.count(it_fruit) > 0) { */
/* 						int NEW_FRUIT = way_to[it_fruit]; */
/* 						if(NEW_FRUIT < FRUIT) { */
/* 							FRUIT = NEW_FRUIT; */
/* 							point = it_step; */
/* 						} */
/* 					} */
/* 				} */
/* 			} */
/* 		} */
/* 	} */
/* 	SetStep(point); */
/* } */

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
