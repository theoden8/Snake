#pragma once

#include <string>

#include "Ball.hpp"

#define WIDTH State::width
#define HEIGHT State::height
#define FOLDER State::folder

class State {
public:
	static std::string
		folder;

	static bool
		pause,
		running;

	static double
		width,
		height,
		x_Display,
		y_Display;

	static int
		latency,
		latency_delta;

public:
	static void Init(const int &argc, char **argv);
	static void Keyboard(char key);
	static void Display();
};
