#include <cassert>
#include <cstdlib>
#include <iostream>

#include "Snake.hpp"
#include "Functions.hpp"
#include "Aimer.hpp"
#include "Router.hpp"
#include "State.hpp"

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

	Crossed.load(FOLDER + "_textures/Cross.tga");
	for(int i = 0; i < NO_ICONSETS; ++i) {
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
void Snake::AutoMove() {
	std::cout << "automatic move triggered" << std::endl;
	Ball target, step;

	aimer->Reset();
	aimer->SetTarget(target);
	router->SetStep(objects.front(), target, step);

	if(safe_walk) {
		Ball overhead = objects.front() + step;
		if(Ball::InSegment(overhead, objects)
		   || Ball::InSegment(overhead, WALLS->GetObjects()))
		{
			int
				bu_aim = aimer->aim,
				bu_route = router->route;
			aimer->aim = 1;
			router->route = 4;

			aimer->SetTarget(target);
			router->SetStep(objects.front(), step, target);

			aimer->aim = bu_aim;
			router->route = bu_route;
		}
	}
	targetLast = target;

	SetStep(step);
}

void Snake::SetStep(Ball &step) {
	if(step == -previousDirection && objects.size() != 1)
		return;

	std::cout << step << std::endl;
	assert(std::abs(step.x) + std::abs(step.y) == 1);

	currentDirection = step;
}

void Snake::DoStep() {
	for(size_t i = objects.size() - 1; i != 0; --i)
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
