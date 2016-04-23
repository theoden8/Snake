#pragma once

#include <string>
#include <map>

#include "Wall.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"
#include "State.hpp"
#include "Aimer.hpp"
#include "Router.hpp"

struct State {
	std::string
	   	folder;
	bool
		pause = true,
		running = false;
	double
		width,
		height,
		x_Display,
		y_Display;
	int
		latency,
		latency_delta = 0;
	std::map <unsigned char, Ball> DoSteps = {
		{'a', Ball(-1, 0)},
		{'w', Ball(0, 1)},
		{'s', Ball(0, -1)},
		{'d', Ball(1, 0)},
	};

	State(int latency, int width, int height);
	void Keyboard(char key);
};
