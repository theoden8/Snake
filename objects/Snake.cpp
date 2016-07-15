#include "Snake.hpp"

#include "Snake.hpp"
#include "State.hpp"
#include "Aimer.hpp"
#include "Router.hpp"

Snake::Snake()
{
	objects.push_back(
		{
			Ball(
				int(State::width) >> 1,
				int(State::height) >> 1
			)
		}
	);
	Crossed.load(State::folder + "_textures/Cross.tga");
	for(int i = 0; i < 8; ++i) {
		skins[i].head.load(State::folder + "_textures/" + std::to_string(i) + "_HEAD.tga");
		skins[i].body.load(State::folder + "_textures/" + std::to_string(i) + "_BODY.tga");
		skins[i].tail.load(State::folder + "_textures/" + std::to_string(i) + "_TAIL.tga");
	}
	aimer = new Aimer(this);
	router = new Router(aimer);
}

Snake::~Snake() {
	delete aimer;
	delete router;
}
