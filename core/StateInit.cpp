#include <cstdlib>
#include <string>

#include "State.hpp"

static void InitState(const int &argc, char **argv) {
	State::latency = 40;
	State::latency_delta = 0;
	State::width = (argc >= 3) ? atoi(argv[1]) : 50;
	State::height = (argc >= 3) ? atoi(argv[2]) : 50;

	State::pause = true;
	State::running = false;

	const std::string exec = argv[0];
	State::folder = exec.substr(0, exec.length() - 6);

	State::x_Display = State::width * 1.4;
	State::y_Display = State::height + 0.5;
}

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
