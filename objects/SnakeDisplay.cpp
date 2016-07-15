#include <cstdlib>

#include "Snake.hpp"
#include "State.hpp"
#include "Graphics.hpp"

#include "Router.hpp"
#include "Aimer.hpp"

void Snake::Keyboard(char key) {
	switch(key) {
		case 'g' :
			safe = !safe;
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
		AutoCorrection(move);
	}
	if(strchr("01234", key)) {
		int num = key - '0';
		++ID %= 8;
		if(router->mode != num) {
			aimer->aim = 1;
			router->mode = num;
		} else {
			++aimer->aim %= 5;
		}
		if(key == '2') {
			router->strategy = (rand() & 1) ? 1 : 1e9;
//		} else if(key == '5') {
//				s->mode = 7;
//				if(!latency_delta)
//					latency = 0;
		}
	}
}

void Snake::Display() {
	char text[20];

	sprintf(text, "mode <%d::%s>", router->mode, router->GetName());
	Graphics::DisplayText(State::width + 1, State::height * 0.06, text);

	sprintf(text, "aim  <%d::%s>", aimer->aim, aimer->GetName());
	Graphics::DisplayText(State::width + 1, State::height * 0.02, text);

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
