#pragma once

#include <map>
#include <string>

#include "Wall.hpp"
#include "Snake.hpp"

struct Snake;

struct Aimer {
	std::map <int, std::string> name;
	int aim;

	Ball target;
	Snake *s;
	Wall *w;

	int &range;
	std::map <Ball, bool> sonar;
	std::map <Ball, int> way_to;

	Aimer();

	void AddObstacle(std::vector <Ball> &objects);
	void DeleteSnakeObstacles();
	void Initialize();
	Ball GetTargetFurthest();
	Ball GetTargetClosest();
	Ball GetTargetNewest();
	Ball GetSnakeTail();
};
