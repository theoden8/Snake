#include <cstdlib>
#include <cstring>

#include "Snake.hpp"
#include "State.hpp"
#include "Graphics.hpp"

#include "Router.hpp"
#include "Aimer.hpp"

void Snake::Keyboard(char key) {
	switch(key) {
		case 'g' :
			safe_walk = !safe_walk;
		break;
	}
	if(strchr("wasd", key)) {
		Ball move;
		switch(key) {
			case 'a':
				move = Ball(-1, 0);
			break;
			case 'w':
				move = Ball(0, 1);
			break;
			case 's':
				move = Ball(0, -1);
			break;
			case 'd':
				move = Ball(1, 0);
			break;
		}
		if(router->mode == 0)
			SetStep(move);
	}
	else if(strchr("01234", key)) {
		const int num = key - '0';
		++ID %= NO_ICONSETS;
		if(num == 0) {
			router->mode = 0;
			aimer->aim = 0;
		} else if(router->mode != num) {
			aimer->aim = 1;
			router->mode = num % (Router::NO_MODES + 1);
			if(router->mode == 0)
				++router->mode;
		} else {
			++aimer->aim %= (Aimer::NO_AIMS + 1);
			if(aimer->aim == 0)
				++aimer->aim;
		}
		if(num == 2) {
			router->strategy = (rand() & 1) ? 1 : 1e9;
		}
	}
}

#define str(x) std::to_string(x)
#include <iostream>
void Snake::Display() {
	glColor3f(1.0f, 1.0f, 0.0f);
	Graphics::DisplayText
		(WIDTH + 1, HEIGHT * 0.06,
		(std::string() + "mode <" + str(router->mode) + "::" + router->GetName() + ">").c_str()
	);

	glColor3f(0.0f, 1.0f, 0.0f);
	Graphics::DisplayText(
		WIDTH + 1, HEIGHT * 0.02,
		(std::string() + "aim  <" + str(aimer->aim) + "::" + aimer->GetName() + ">").c_str()
	);

	if(safe_walk) {
		glColor3f(1.0f, 0.0f, 0.0f);
		Graphics::DisplayText(
			WIDTH + 1, HEIGHT * 0.10,
			"[Insurance]"
		);
	}

	for(int i = 0; i < objects.size(); ++i) {
		Ball &slice = objects[i];
		Skin &skin = skins[ID];
		GLuint id;
		double degree = 90;
		if(i == 0) {
			id = skin.head.id;
			degree = currentDirection.degree();
		} else if(i == objects.size() - 1) {
			id = skin.body.id;
			degree = (objects[i - 1] - objects[i]).degree();
		} else {
			id = skin.tail.id;
			degree = (objects[i - 1] - objects[i]).degree();
		}
		Graphics::DisplayObject(slice, id, degree);
	}
}
