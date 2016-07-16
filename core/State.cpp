#include <cstdlib>

#include "State.hpp"

void State::Init(const int &argc, char **argv) {
	State::latency = 40;
	State::latency_delta = 0;
	WIDTH = (argc >= 3) ? atoi(argv[1]) : 50;
	HEIGHT = (argc >= 3) ? atoi(argv[2]) : 50;

	State::pause = true;
	State::running = false;

	const std::string exec = argv[0];
	State::folder = exec.substr(0, exec.length() - 6);

	State::x_Display = WIDTH * 1.4;
	State::y_Display = HEIGHT + 0.5;
}
