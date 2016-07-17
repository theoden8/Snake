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

public:
	Image IMG_TARGET;
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
		snakeLast,
		targetLast;
	bool
		growNextMove = false,
		safe_walk = false;

public:
	Snake();
	~Snake();

	const Ball &head() const;
	const Ball &tail() const;

	void Display();
	void Keyboard(char key);

	/* void AutoCorrection(Ball arrow); */
	void AutoSetStep();
	void DoStep();
	void PushBack();

private:
	void SetStep(Ball &step);
};
