#include <cstring>
#include <cstdlib>
#include <iostream>

#include "State.hpp"
#include "Graphics.hpp"

#include "Snake.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"

bool
	State::pause = true,
	State::running = false;

int
	State::latency = 40,
	State::latency_delta = 0,
	State::skin_id = 0;

double
	State::width = 50,
	State::height = 50;

double
	State::x_Display = WIDTH * 1.4,
	State::y_Display = HEIGHT * 0.5;

std::string
	State::folder = "";

Object
	*WALLS,
	*FRUITS,
	*SNAKE;

void State::Init(const int &argc, char **argv) {
	WIDTH = (argc >= 3) ? atoi(argv[1]) : 50;
	HEIGHT = (argc >= 3) ? atoi(argv[2]) : 50;

	const std::string exec = argv[0];
	folder = exec.substr(0, exec.length() - strlen("_snake"));

	x_Display = WIDTH * 1.4;
	y_Display = HEIGHT + 0.5;
}


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

	if(strchr("0123456789", key)) {
		latency = (key == '0') ? 40 : 0;
		++skin_id %= NO_ICONSETS;
	}
}

void State::Display() {
	char text[20];

	glColor3f(1.0f, 1.0f, 1.0f);
	sprintf(text, "Latency: %d", State::latency);
	Graphics::DisplayText(WIDTH + 1, HEIGHT * 0.89, text);

	glColor3f(0.3f, 0.3f, 1.0f);
	if(State::pause) {
		sprintf(text, "[Paused]");
		Graphics::DisplayText(WIDTH * 0.45, HEIGHT * 0.75, text);
	}

	glColor3f(1.0f, 0.3f, 0.3f);
	if(State::running) {
		sprintf(text, "[Running]");
		Graphics::DisplayText(WIDTH * 0.45, HEIGHT * 0.25, text);
	}
}

void State::Timer() {
	if(!State::pause) {
		if(!State::running)
			SSNAKE->DoStep();
		if(
			Ball::InSegment(SNAKE->GetObjects().front(), WALLS->GetObjects())
			|| Ball::InSegment(SNAKE->GetObjects().front(), SNAKE->GetObjects(), Ball(1, SNAKE->GetObjects().size()))
		)
		{
			std::cout << std::to_string(FFRUITS->frufru) << std::endl;
			exit(0);
		}
	}
	if(Ball::InSegment(SNAKE->GetObjects().front(), FRUITS->GetObjects()))
		FFRUITS->EatFruit();

	SSNAKE->AutoMove();
}
