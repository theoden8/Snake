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
struct Router;

struct Skin {
	Image head, body, tail;
	Skin(Image h, Image b, Image t):
		head(h), body(b), tail(t)
	{}
};

struct Snake {
	Aimer &aimer;
	Router &router;

	static Skin skins[8];
	Image Crossed;
	std::vector <Ball> snake;

	int
		ID = 0,
		mode = 0,
		aim = 0,
		strategy = 2;
	Ball
		currentDirection = Ball(0, -1),
		snakeLast,
		previousDirection = Ball(0, 0);
	bool
		growNextMove = false,
		safe = false;

	Snake(std::string folder, int x, int y, Aimer &aimer, Router &r);
	void Keyboard(char key);
	void AutoCorrection(Ball arrow, Wall *c, Fruit *f);
	void AutomaticMove(Wall *c, Fruit *f);
	void AutoCD_C(Wall *c, Fruit *f);
	void AddObstacle(std::map <Ball, bool> &sonar, std::vector <Ball> &objects);
	void DeleteSnakeObstacles (std::map <Ball, bool> &sonar, Ball &from);
	std::vector <Ball> GetStepsSpaciest(std::map <Ball, bool> &sonar, Ball &from);
	void DoStep();
	void SetStep(Ball &point);
	void Push_Back();
};
