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

	Wall *walls = NULL;
	Fruit *fruits = NULL;
	Snake *snake = NULL;

	State(int latency, int width, int height);
	void Keyboard(char key);
	void Display();
};
