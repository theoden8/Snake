#include <cstdlib>
#include <cmath>

#include "State.hpp"
#include "Functions.hpp"
#include "Graphics.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"
#include "Router.hpp"
#include "Aimer.hpp"


static void InitState(const int &argc, char **argv) {
	State::latency = 40;
	State::latency_delta = 0;
	State::width = (argc >= 3) ? atoi(argv[1]) : 50;
	State::height = (argc >= 3) ? atoi(argv[2]) : 50;

	State::pause = true;
	State::running = false;

	const std::string exec = argv[0];
	State::folder = exec.substr(0, exec.length() - 6);

	State::x_Display = State::width * 1.4;
	State::y_Display = State::height + 0.5;
}


void State::Keyboard(char key) {
	switch(key) {
		case 27 :
			exit(0);
		break;
		case 'p' :
			pause = !pause;
		break;
		case 't' :
			running = !running;
		break;
		case 'o' :
			if(latency_delta > 0)
				latency_delta = 0;
			latency = (latency > (abs(--latency_delta) >> 3) + 1) ? (latency - ((abs(latency_delta) >> 3) + 1)) : 0;
		break;
		case 'i' :
			if(latency_delta < 0)
				latency_delta = 0;
			latency += ((++latency_delta) >> 3) + 1;
		break;
	}

	if(strchr("0123456789", key))
		latency = (key == '0') ? 40 : 0;
}

void State::Display() {
	glOrtho(-0.5, x_Display, -0.5, y_Display, -10, 10);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);

	char text[20];

	sprintf(text, "Points: %d..", fruits->frufru);
	Graphics::DrawText(width + 1, height * 0.97, text);

	sprintf(text, "Fruits: %lu", fruits->fruitStorage.size());
	Graphics::DrawText(width + 1, height * 0.93, text);

	sprintf(text, "Latency: %d", latency);
	Graphics::DrawText(width + 1, height * 0.89, text);

	if(pause) {
		sprintf(text, "[Paused]");
		Graphics::DrawText(width * 0.45, height * 0.75, text);
    }
	if(running) {
		sprintf(text, "[Running]");
		Graphics::DrawText(width * 0.45, height * 0.25, text);
    }
	if(snake->safe) {
		sprintf(text, "    [Insurance]");
		Graphics::DrawText(width + 1, height * 0.10, text);
    }

	sprintf(text, "mode <%d::%s>", snake->mode, Router::GetName(snake->mode, snake->strategy));
	Graphics::DrawText(width + 1, height * 0.06, text);

	sprintf(text, "aim  <%d::%s>", snake->aim, Aimer::GetName(snake->aim));
	Graphics::DrawText(width + 1, height * 0.02, text);

	glEnable(GL_TEXTURE_2D);
}
