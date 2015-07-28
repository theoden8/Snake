#pragma once

#include <vector>
#include <string>
#include <map>

#include "Imagg.hpp"
#include "Ball.hpp"
#include "Aimer.hpp"
#include "Router.hpp"

struct Walls;
struct Fruits;

struct Snakes {
	Imagg head[8];
	Imagg body[8];
	Imagg tail[8];
	Imagg Crossed;
	std::vector <Ball> snake;

	std::map <int, std::string> ModeName, AimName;
	int ID, mode, aim,
	    modeN, aimN,
	    strategy,
	    controller,
	    X, Y;
	Ball varDirection,
	     varSnakesLast,
	     varPreviousDirection;
	bool varGrowNextMove,
	     safe;

	Snakes(std::string folder, int x, int y);
	void Keyboard		(char key);
	void AutoCorrection	(Ball arrow, Walls *c, Fruits *f);
	void ArtificialMove	(Walls *c, Fruits *f);
	void AutoCD_C		(Walls *c, Fruits *f);
	void AddObstacle	(std::map <Ball, bool> &sonar, std::vector <Ball> &objects);
	void DeleteSnakesObstacles (std::map <Ball, bool> &sonar, Ball &from);
	Ball GetSnakesTail	(int &range, std::map <Ball, bool> &sonar, Ball &from);
	Ball GetClosestFruit	(Fruits *f, int &range, std::map <Ball, bool> &sonar, Ball &from);
	Ball GetNewestFruit	(Fruits *f, int &range, std::map <Ball, bool> &sonar, Ball &from);
	Ball GetFurthestFruit	(Fruits *f, int &range, std::map <Ball, bool> &sonar, Ball &from);
	Ball GetPointStraight	(Walls *c, Ball &target, int &strategy);
	Ball GetPointShortest	(int range, std::map <Ball, bool> &sonar, Ball &from, Ball &target);
	std::vector <Ball> GetStepsSpaciest (std::map <Ball, bool> &sonar, Ball &from);
	void DoStep		();
	void SetStep		(Ball &point);
	void Push_Back		();
};
