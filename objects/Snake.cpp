#include <cassert>
#include <cstdlib>
#include <iostream>

#include "Snake.hpp"
#include "Functions.hpp"
#include "Aimer.hpp"
#include "Router.hpp"
#include "State.hpp"

#include <iostream>

Snake::Snake()
{
	objects.push_back(
		{
			Ball(
				WIDTH >> 1,
				HEIGHT >> 1
			)
		}
	);

	IMG_TARGET.load(FOLDER + "_textures/TARGET.tga");
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

const Ball &Snake::head() const {
	return objects.front();
}

const Ball &Snake::tail() const {
	return objects.back();
}


Ball Snake::GetAutoStep() {
	/* std::cout << "automove" << std::endl; */

	aimer->Reset();
	Ball step = router->GetStep();

	/* if(safe_walk) { */
	/* 	Ball overhead = objects.front() + step; */
	/* 	if(Ball::InSegment(overhead, objects) */
	/* 	   || Ball::InSegment(overhead, WALLS->GetObjects())) */
	/* 	{ */
	/* 		int */
	/* 			bu_aim = aimer->aim, */
	/* 			bu_route = router->route; */
	/* 		aimer->aim = 1; */
	/* 		router->route = 4; */

	/* 		step = router->GetStep(); */

	/* 		aimer->aim = bu_aim; */
	/* 		router->route = bu_route; */
	/* 	} */
	/* } */
	targetLast = aimer->GetTarget();

	return step;
}

void Snake::SetStep(Ball step) {
	if(step == -previousDirection && objects.size() != 1)
		return;

	std::cout << step << std::endl;
	assert(step.is_valid_step());
	assert((head() + step).is_valid_position());

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
