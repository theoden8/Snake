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
		/* AutoCorrection(move); */
	}
	else if(strchr("01234", key)) {
		const int num = key - '0';
		++ID %= 8;
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

void Snake::Display() {
	char text[20];

	glColor3f(1.0f, 1.0f, 0.0f);
	sprintf(text, "mode <%d::%s>", router->mode, router->GetName());
	Graphics::DisplayText(WIDTH + 1, HEIGHT * 0.06, text);

	glColor3f(0.0f, 1.0f, 0.0f);
	sprintf(text, "aim  <%d::%s>", aimer->aim, aimer->GetName());
	Graphics::DisplayText(WIDTH + 1, HEIGHT * 0.02, text);

	if(safe_walk) {
		glColor3f(1.0f, 0.0f, 0.0f);
		sprintf(text, "[Insurance]");
		Graphics::DisplayText(WIDTH + 1, HEIGHT * 0.10, text);
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
