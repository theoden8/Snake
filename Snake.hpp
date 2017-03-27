#pragma once

#include <vector>
#include <map>

#include "Object.hpp"
#include "State.hpp"

class Aimer;
class Router;

class Snake : public Object {
	struct Skin {
		Image head, body, tail;
		Skin() {}
		Skin(Image h, Image b, Image t):
			head(h), body(b), tail(t)
		{}
	};
	Skin skins[NO_ICONSETS];

	Aimer *aimer;
	Router *router;

	bool
		growNextMove = false,
		safe_walk = false;

	Ball
		previousDirection = Ball(-1, 0),
		snakeLast;

public:
	Image IMG_TARGET;

	Ball
		currentDirection = previousDirection,
		targetLast;

public:
	Snake();
	~Snake();

	const Ball &head() const;
	const Ball &tail() const;

	void Display();
	void Keyboard(char key);

	Ball GetAutoStep();
	void DoStep();
	void PushBack();
	void SetStep(Ball step);
};
