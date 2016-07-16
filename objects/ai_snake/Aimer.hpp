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
	const Snake *snake;
	std::map <Ball, bool> sonar;
public:
	int aim = 0;
	const static int NO_AIMS;

public:
	Aimer(Snake *s);
	const char *GetName() const;
	const Snake *GetSnake() const;
	const std::map <Ball, bool> &GetSonar();

	void Scan();
	void Reset();

	void SetTarget(Ball &target);
private:
	void SetTargetClosestFruit(Ball &target);
	void SetTargetNewestFruit(Ball &target);
	void SetTargetFurthestFruit(Ball &target);
	void SetTargetSnakeTail(Ball &target);
};
