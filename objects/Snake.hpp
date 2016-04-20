#pragma once

#include <vector>
#include <string>
#include <map>

#include "Image.hpp"
#include "Ball.hpp"
#include "Aimer.hpp"
#include "Router.hpp"

struct Wall;
struct Fruit;

struct Snake {
	Imagg head[8];
	Imagg body[8];
	Imagg tail[8];
	Imagg Crossed;
	std::vector <Ball> snake;

	int ID, mode, aim,
		modeN, aimN,
		strategy,
	Ball currentDirection,
		 snakeLast,
		 previousDirection;
	bool growNextMove,
		 safe;

	Snake(std::string folder, int x, int y);
	void Keyboard		(char key);
	void AutoCorrection	(Ball arrow, Wall *c, Fruit *f);
	void ArtificialMove	(Wall *c, Fruit *f);
	void AutoCD_C		(Wall *c, Fruit *f);
	void AddObstacle	(std::map <Ball, bool> &sonar, std::vector <Ball> &objects);
	void DeleteSnakeObstacles (std::map <Ball, bool> &sonar, Ball &from);
	Ball GetSnakeTail	(int &range, std::map <Ball, bool> &sonar, Ball &from);
	Ball GetClosestFruit	(Fruit *f, int &range, std::map <Ball, bool> &sonar, Ball &from);
	Ball GetNewestFruit	(Fruit *f, int &range, std::map <Ball, bool> &sonar, Ball &from);
	Ball GetFurthestFruit	(Fruit *f, int &range, std::map <Ball, bool> &sonar, Ball &from);
	Ball GetPointStraight	(Wall *c, Ball &target, int &strategy);
	Ball GetPointShortest	(int range, std::map <Ball, bool> &sonar, Ball &from, Ball &target);
	std::vector <Ball> GetStepsSpaciest (std::map <Ball, bool> &sonar, Ball &from);
	void DoStep		();
	void SetStep		(Ball &point);
	void Push_Back		();
};
