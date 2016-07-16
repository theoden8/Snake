#include <string>
#include <cstring>
#include <cstdlib>

#include "State.hpp"
#include "Graphics.hpp"

void State::Keyboard(char key) {
	switch(key) {
		case 27 :
			exit(0);
		break;
		case 'p' :
			pause = !pause;
		break;
		case 'r' :
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
	char text[20];

	glColor3f(1.0f, 1.0f, 1.0f);
	sprintf(text, "Latency: %d", State::latency);
	Graphics::DisplayText(WIDTH + 1, HEIGHT * 0.89, text);

	if(State::pause) {
		glColor3f(0.3f, 0.3f, 1.0f);
		sprintf(text, "[Paused]");
		Graphics::DisplayText(WIDTH * 0.45, HEIGHT * 0.75, text);
	}

	if(State::running) {
		glColor3f(1.0f, 0.3f, 0.3f);
		sprintf(text, "[Running]");
		Graphics::DisplayText(WIDTH * 0.45, HEIGHT * 0.25, text);
	}
}
