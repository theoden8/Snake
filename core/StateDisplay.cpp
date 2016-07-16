#include "State.hpp"
#include "Graphics.hpp"

void State::Display() {
	char text[20];

	if(State::pause) {
		sprintf(text, "[Paused]");
		Graphics::DisplayText(WIDTH * 0.45, HEIGHT * 0.75, text);
	}

	if(State::running) {
		sprintf(text, "[Running]");
		Graphics::DisplayText(WIDTH * 0.45, HEIGHT * 0.25, text);
	}
}
