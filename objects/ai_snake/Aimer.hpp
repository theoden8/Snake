#pragma once

#include <map>
#include <string>

#include "Ball.hpp"

#define UNDEF_INT -1

class Object;
class Snake;

class Aimer {
	const Snake *snake;
	std::map <Ball, bool> sonar;
public:
	int aim = 0,
		range = UNDEF_INT;
	const static int NO_AIMS;

public:
	Aimer(Snake *s);
	const char *GetName() const;
	const Snake *GetSnake() const;
	const std::map <Ball, bool> &GetSonar();

	void Scan();
	void Reset();

	Ball GetTarget();
private:
	void SetTargetClosestFruit(Ball &target);
	void SetTargetNewestFruit(Ball &target);
	void SetTargetFurthestFruit(Ball &target);
	void SetTargetSnakeTail(Ball &target);
};
