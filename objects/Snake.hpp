#pragma once

#include <vector>
#include <string>
#include <map>

#include "Image.hpp"

class Aimer;
class Router;

class Snake {
	struct Skin {
		Image head, body, tail;
		Skin(Image h, Image b, Image t):
			head(h), body(b), tail(t)
		{}
	};

	Aimer *aimer;
	Router *router;

	static Skin skins[8];
	Image Crossed;

public:
	std::vector <Ball> snake;

	int
		ID = 0, strategy = 2,
		mode = 0, aim = 0;
	Ball
		currentDirection = Ball(0, -1),
		previousDirection = Ball(0, 0),
		snakeLast;
	bool
		growNextMove = false,
		safe = false;

public:
	Snake();
	void Keyboard(char key);
	void Display();

	void AutoCorrection(Ball arrow);
	void AutomaticMove();
	/* void AutoCD_C(); */
	void AddObstacle(std::map <Ball, bool> &sonar, std::vector <Ball> &objects);
	void DeleteSnakeObstacles (std::map <Ball, bool> &sonar, Ball &from);
	void DoStep();
	void SetStep(Ball &point);
	void Push_Back();
};
