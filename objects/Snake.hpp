#pragma once

#include <vector>
#include <map>

#include "Object.hpp"
#include "State.hpp"

class Aimer;
class Router;

class Snake : public Object {
	Aimer *aimer;
	Router *router;

	Image Crossed;
public:
	struct Skin {
		Image head, body, tail;
		Skin() {}
		Skin(Image h, Image b, Image t):
			head(h), body(b), tail(t)
		{}
	};
	Skin skins[NO_ICONSETS];

	Ball
		currentDirection = Ball(-1, 0),
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

	/* void AutoCorrection(Ball arrow); */
	void AutoMove();
	void SetStep(Ball &step);
	void DoStep();
	void PushBack();
};
