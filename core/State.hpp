#pragma once

#include <string>
#include <map>
#include "Ball.hpp"

struct State {
	std::string folder;
	bool pause,
	     running;
	double width,
	       height,
	       x_Display,
	       y_Display;
	int latency,
	    latency_delta;
	std::map <unsigned char, Ball> DoSteps;
	State(int latency, bool pause, int width, int height);
	void Keyboard(char key);
};
