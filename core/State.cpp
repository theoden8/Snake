#include <cstdlib>

#include "State.hpp"
#include "Functions.hpp"

State::State(int latency, bool pause1, int width, int height) :
	pause1(pause1), running(0),
	width(width), height(height),
	latency(latency), latency_delta(0)
{
	DoSteps['a'] = Ball(-1, 0);
	DoSteps['w'] = Ball(0, 1);
	DoSteps['s'] = Ball(0, -1);
	DoSteps['d'] = Ball(1, 0);
}
void State::Keyboard(char key) {
	switch(key) {
		case 27 :
			exit(0);
			break;
		case 'p' :
			pause1 = !pause1;
			break;
		case 't' :
			running = !running;
			break;
		case 'o' :
			if(latency_delta > 0) {
				latency_delta = 0;
			}
			latency = (latency > (abs(--latency_delta) >> 3) + 1) ? (latency - ((abs(latency_delta) >> 3) + 1)) : 0;
			break;
		case 'i' :
			if(latency_delta < 0) {
				latency_delta = 0;
			}
			latency += ((++latency_delta) >> 3) + 1;
			break;
	}
	if(process_key("0123456789", key)) {
		if(!latency_delta) {
			latency = 0;
		}
		if(key == '0') {
			latency = 40;
		}
		return;
	}
}
