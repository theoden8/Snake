#include <cstdlib>
#include <cstdio>

#include "State.hpp"

#include "Fruit.hpp"
#include "Snake.hpp"
#include "Router.hpp"
#include "Aimer.hpp"
#include "Graphics.hpp"


void State::Display() {
	char text[20];

	sprintf(text, "Points: %d..", FFRUITS->frufru);
	Graphics::DisplayText(width + 1, height * 0.97, text);

	sprintf(text, "Fruits: %lu", FRUITS->GetObjects().size());
	Graphics::DisplayText(width + 1, height * 0.93, text);

	sprintf(text, "Latency: %d", State::latency);
	Graphics::DisplayText(width + 1, height * 0.89, text);

	if(State::pause) {
		sprintf(text, "[Paused]");
		Graphics::DisplayText(width * 0.45, height * 0.75, text);
	}
	if(State::running) {
		sprintf(text, "[Running]");
		Graphics::DisplayText(width * 0.45, height * 0.25, text);
	}
	if(SSNAKE->safe) {
		sprintf(text, "    [Insurance]");
		Graphics::DisplayText(width + 1, height * 0.10, text);
	}
}
