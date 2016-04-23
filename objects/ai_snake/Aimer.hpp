#pragma once

#include <map>
#include <string>

#include "Wall.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"

#define INVALID_INT -1

struct Snake;

// provides the aim for a snake
struct Aimer {
	Snake *s;
	Wall *w;
	Fruit *f;

	int range = INVALID_INT;
	std::map <Ball, bool> sonar;
	std::map <Ball, int> way_to;

	Aimer(Snake *s, Wall *w, Fruit *f);

	static char *GetName(int aim);
	void SetTarget(Ball &target, int aim);
private:
	void AddObstacle(std::vector <Ball> &objects);
	void DeleteSnakeObstacles();
	Ball GetTargetFurthest(const Ball &target);
	Ball GetTargetClosest(const Ball &target);
	Ball GetTargetNewest(const Ball &target);
	Ball GetSnakeTail(const Ball &target);
};
