#include <cstdlib>
#include <cstring>

#include <string>

#include "State.hpp"

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
