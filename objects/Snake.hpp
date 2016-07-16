#pragma once

#include <vector>
#include <map>

#include "Object.hpp"

class Aimer;
class Router;

class Snake : public Object {
	Aimer *aimer;
	Router *router;

	/* Image Crossed; */
public:
	struct Skin {
		Image head, body, tail;
		Skin() {}
		Skin(Image h, Image b, Image t):
			head(h), body(b), tail(t)
		{}
	};
	Skin skins[8];

	int
		ID = 0;
	Ball
		currentDirection = Ball(0, -1),
		previousDirection = Ball(0, 0),
		snakeLast;
	bool
		growNextMove = false,
		safe_walk = false;

public:
	Snake();
	~Snake();
	void Display();

	void Keyboard(char key);

	void AutoCorrection(Ball arrow);
	void AutomaticMove();
	void AddObstacle(std::map <Ball, bool> &sonar, std::vector <Ball> &objects);
	void DeleteSnakeObstacles (std::map <Ball, bool> &sonar, Ball &from);
	void DoStep();
	void SetStep(Ball &point);
	void PushBack();
};
