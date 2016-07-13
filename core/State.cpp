#include <cstdlib>
#include <cmath>

#include "State.hpp"
#include "Functions.hpp"

State::State(int latency, int width, int height) :
	latency(latency),
	width(width),
	height(height)
{}

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
	glOrtho(-0.5, state->x_Display, -0.5, state->y_Display, -10, 10);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);

	char text[20];

	sprintf(text, "Points: %d..", fruits->frufru);
	Graphics::DrawTest(width + 1, height * 0.97, text);

	sprintf(text, "Fruits: %d", fruits->fruitStorage.size());
	Graphics::DrawTest(width + 1, height * 0.93, text);

	sprintf(text, "Latency: %d", latency);
	Graphics::DrawTest(width + 1, height * 0.89, text);

	if(pause)
		Graphics::DrawText(width * 0.45, height * 0.75, "[Paused]");
	if(running)
		Graphics::DrawText(width * 0.45, height * 0.25, "[Running]");
	if(snake->safe)
		Graphics::DrawText(width + 1, height * 0.10, "   [Insurance]");

	sprintf(mode, "mode <%d::%s>", snake->mode, Rounter::GetName(snake->mode, snake->strategy));
	Graphics::DrawText(width + 1, height * 0.06, text);

	sprintf(mode, "aim  <%d::%s>", snake->aim, Aimer::GetName(snake->ain));
	Graphics::DrawText(width + 1, height * 0.02, text);

	glEnable(GL_TEXTURE_2D);
}
