#pragma once

#include <map>
#include <string>

#include "Ball.hpp"

#define INVALID_INT -1

class Object;
class Snake;

class Aimer {
	int
		range = INVALID_INT;
	std::map <Ball, int> way_to;
	const Snake *snake;
public:
	int aim = 0;
	const static int NO_AIMS;
	std::map <Ball, bool> sonar;
	/* Aimer(); */

public:
	Aimer(Snake *s);
	const char *GetName() const;
	const Snake *GetSnake() const;
	void SetTarget(Ball &target);
private:
	void SetSonar();

	void SetTargetClosestFruit(Ball &target);
	void SetTargetNewestFruit(Ball &target);
	void SetTargetFurthestFruit(Ball &target);
	void SetTargetSnakeTail(Ball &target);
};
