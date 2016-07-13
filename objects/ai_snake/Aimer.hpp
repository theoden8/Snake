#pragma once

#include <map>
#include <string>

#include "Ball.hpp"

class Snake;

#define INVALID_INT -1

class Aimer {
	int range = INVALID_INT;
	std::map <Ball, bool> sonar;
	std::map <Ball, int> way_to;
public:
	Aimer();
	static const char *GetName(int aim);
	void SetTarget(Ball &target, int aim);
private:
	void AddObstacle(std::vector <Ball> &objects);
	void DeleteSnakeObstacles();
	void SetTargetFurthest(Ball &target);
	void SetTargetClosest(Ball &target);
	void SetTargetNewest(Ball &target);
	void SetTargetSnakeTail(Ball &target);
};
