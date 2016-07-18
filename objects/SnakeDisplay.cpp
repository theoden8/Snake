#include <cstdlib>
#include <cstring>

#include "Snake.hpp"
#include "State.hpp"
#include "Graphics.hpp"
#include "Router.hpp"
#include "Aimer.hpp"

void Snake::Keyboard(char key) {
	static const int HUMAN = 0;

	switch(key) {
		case 'g' :
			safe_walk = !safe_walk;
		break;
	}
	if(strchr("wasd", key) && router->route == HUMAN) {
		Ball step;
		switch(key) {
			case 'a':
				step = Ball(-1, 0);
			break;
			case 'w':
				step = Ball(0, 1);
			break;
			case 's':
				step = Ball(0, -1);
			break;
			case 'd':
				step = Ball(1, 0);
			break;
		}
		SetStep(step);
	}

	if('0' <= key && key < '0' + Router::NO_ROUTES) {
		const int num = key - '0';

		if(router->route != num) {
			router->route = num;
			aimer->aim = (router->route == HUMAN) ? HUMAN : 1;
		} else {
			const int abegin = (router->route == HUMAN) ? 0 : 1;
			++aimer->aim;
			if(aimer->aim == Aimer::NO_AIMS)
				aimer->aim = abegin;
		}

		if(num == 2)
			router->strategy = (rand() & 1) ? 1 : 1e9;

	}
}

#define str(x) std::to_string(x)
void Snake::Display() {
	glColor3f(1.0f, 0.0f, 0.0f);
	if(safe_walk) {
		Graphics::DisplayText(
			WIDTH + 1, HEIGHT * 0.10,
			"[Insurance]"
		);
	}

	glColor3f(1.0f, 1.0f, 0.0f);
	Graphics::DisplayText
		(WIDTH + 1, HEIGHT * 0.06,
		(std::string() + "route <" + str(router->route) + "::" + router->Name() + ">").c_str()
	);

	glColor3f(0.0f, 1.0f, 0.0f);
	Graphics::DisplayText(
		WIDTH + 1, HEIGHT * 0.02,
		(std::string() + "aim  <" + str(aimer->aim) + "::" + aimer->Name() + ">").c_str()
	);

	for(int i = 0; i < objects.size(); ++i) {
		Ball &slice = objects[i];
		double degree = 90;
		Skin &skin = skins[State::skin_id];
		GLuint id;
		if(i == 0) {
			id = skin.head.id;
			degree = currentDirection.degree();
		} else if(i == objects.size() - 1) {
			id = skin.tail.id;
			degree = (objects[i - 1] - objects[i]).degree();
		} else {
			id = skin.body.id;
			degree = (objects[i - 1] - objects[i]).degree();
		}
		Graphics::DisplayObject(slice, id, degree);
	}
	if(targetLast.is_valid_position())
		Graphics::DisplayObject(targetLast, IMG_TARGET.id, 90);
}
