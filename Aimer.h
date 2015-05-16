#pragma once

#include <map>
#include <string>

struct Aimer {
	std::map <int, std::string> name;
	int aim;

	Ball target;
	Walls *w;
	int &range;
	std::map <Ball, bool> sonar;
	std::map <Ball, int> way_to;

	Aimer ();

	void AddObstacle(std::vector <Ball> &objects);
	void DeleteSnakesObstacles();
	void Initialize();
	Ball GetTargetFurthest();
	Ball GetTargetClosest();
	Ball GetTargetNewest();
	Ball GetSnakeTail();
};
