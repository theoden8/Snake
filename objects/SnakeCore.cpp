#include <math.h>
#include <cstdlib>
#include <iostream>

#include "Snake.hpp"
#include "Functions.hpp"


void Snake::AutoCorrection(Ball point) {
	/* if( */
	/* 	router.sonar[objects.front() + point] */
	/* 	&& safe */
	/* ) */
	/* { */
	/* 	std::map <Ball, bool> sonar; */
	/* 	AddObstacle(sonar, WALLS->objects); */
	/* 	AddObstacle(sonar, objects); */
	/* 	AutoCD_C(); */
	/* } else { */
	/*	SetStep(point); */
	/* } */
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
