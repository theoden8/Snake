#include <iostream>

#include "Snake.hpp"
#include "Functions.hpp"
#include "State.hpp"
#include "Aimer.hpp"
#include "Router.hpp"

Snake::Snake()
{
	objects.push_back(
		{
			Ball(
				int(WIDTH) >> 1,
				int(HEIGHT) >> 1
			)
		}
	);

	/* Crossed.load(FOLDER + "_textures/Cross.tga"); */
	for(int i = 0; i < 8; ++i) {
		skins[i].head.load(FOLDER + "_textures/" + std::to_string(i) + "_HEAD.tga");
		skins[i].body.load(FOLDER + "_textures/" + std::to_string(i) + "_BODY.tga");
		skins[i].tail.load(FOLDER + "_textures/" + std::to_string(i) + "_TAIL.tga");
	}

	aimer = new Aimer(this);
	router = new Router(aimer);
}

Snake::~Snake() {
	delete aimer;
	delete router;
}


#include <iostream>
void Snake::AutomaticMove() {
	std::cout << "automatic move triggered" << std::endl;
	Ball
		target,
		point;
	aimer->SetTarget(target);
	router->SetPoint(objects.front(), point, target);
	SetStep(point);
}

void Snake::AddObstacle(std::map <Ball, bool> &sonar, std::vector <Ball> &objects) {
	for(auto ball : objects)
		sonar[ball] = true;
}

void Snake::DeleteSnakeObstacles(std::map <Ball, bool> &sonar, Ball &from) {
	std::map <Ball, int> way_to = bfs(sonar, from);
	for(int i = 1; i < objects.size(); ++i) {
		if(way_to[objects[i]] > objects.size() - i)
			sonar.erase(objects[i]);
	}
}


void Snake::SetStep(Ball &point) {
	if(point == -previousDirection)
		return;

	currentDirection = point;
}

void Snake::DoStep() {
	for(int i = objects.size() - 1; i != 0; --i)
		objects[i] = objects[i - 1];

	objects[0] += currentDirection;
	if(growNextMove) {
		objects.push_back(snakeLast);
		growNextMove = false;
	}

	previousDirection = currentDirection;
}

void Snake::PushBack() {
	snakeLast = objects.back();
	growNextMove = true;
}

/* void Snake::AutoCD_C() { */
/* 	std::map <Ball, bool> sonar; */
/* 		AddObstacle(sonar, WALLS->objects); */
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
/* 				for(const auto &it_fruit : FRUITS->objects) { */
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
