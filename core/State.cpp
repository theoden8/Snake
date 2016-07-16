#include <cstdlib>

#include "State.hpp"

bool
	State::pause = true,
	State::running = false;

int
	State::latency = 40,
	State::latency_delta = 0;

double
	State::width = 50,
	State::height = 50;

double
	State::x_Display = WIDTH * 1.4,
	State::y_Display = HEIGHT * 0.5;

std::string
	State::folder = "";

void State::Init(const int &argc, char **argv) {
	/* latency = 40; */
	/* latency_delta = 0; */
	WIDTH = (argc >= 3) ? atoi(argv[1]) : 50;
	HEIGHT = (argc >= 3) ? atoi(argv[2]) : 50;

	/* pause = true; */
	/* running = false; */

	const std::string exec = argv[0];
	folder = exec.substr(0, exec.length() - 6);

	/* x_Display = WIDTH * 1.4; */
	/* y_Display = HEIGHT + 0.5; */
}
