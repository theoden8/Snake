#pragma once

#include <map>
#include <string>

#include "Wall.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"

struct Snake;

// provides the aim for a snake
struct Aimer {
	static const int DEFAULT_RANGE;

	std::map <int, std::string> name;

	Ball *from = NULL, *target = NULL;

	Snake *s;
	Wall *w;
	Fruit *f;

	int range = DEFAULT_RANGE;
	std::map <Ball, bool> sonar;
	std::map <Ball, int> way_to;

	Aimer(Snake *s, Wall *w, Fruit *f);

	static char *GetName(int aim);
	Ball GetTarget(int aim);
private:
	void AddObstacle(std::vector <Ball> &objects);
	void DeleteSnakeObstacles();
	Ball GetTargetFurthest();
	Ball GetTargetClosest();
	Ball GetTargetNewest();
	Ball GetSnakeTail();
};
