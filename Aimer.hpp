#pragma once

#include <map>

#include "Ball.hpp"

class Object;
class Snake;

class Aimer {
	const Snake *snake;
	std::map <Ball, bool> sonar;
	std::map <Ball, int> distances_head;
	Ball target;
public:
	int aim = 0;
	const static int NO_AIMS;

public:
	Aimer(Snake *s);
	const char *Name() const;
	const Snake *GetSnake() const;

	const std::map <Ball, bool> &Sonar();
	void SonarToggleHead();
	std::map <Ball, int> &DistancesHead();

	void Scan();
	void Reset();

	Ball GetTarget();
private:
	void SetTargetClosestFruit();
	void SetTargetRandomFruit();
	void SetTargetFurthestFruit();
	void SetTargetSnakeTail();
};
