#pragma once

#include <map>
#include <string>

#include "Wall.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"
#include "Functions.hpp"

#define INVALID_INT -1

struct Snake;

// provides the aim for a snake
class Aimer {
	Snake *s;
	Wall *w;
	Fruit *f;

	int range = INVALID_INT;
	std::map <Ball, bool> sonar;
	std::map <Ball, int> way_to;
public:
	Aimer(Snake *s, Wall *w, Fruit *f);
	static char *GetName(int aim);
	void SetTarget(Ball &target, int aim);
private:
	void AddObstacle(std::vector <Ball> &objects);
	void DeleteSnakeObstacles();
	void SetTargetFurthest(Ball &target);
	void SetTargetClosest(Ball &target);
	void SetTargetNewest(Ball &target);
	void SetTargetSnakeTail(Ball &target);
};
