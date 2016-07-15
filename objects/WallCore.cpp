#include "Wall.hpp"
#include "State.hpp"

Wall::Wall() {
	for(int i = 0; i <= 0; ++i)
		wallsGallery[i].load(State::folder + "_textures/" + std::to_string(i) + "_WALL.tga");

	for(int i = 0; i <= State::width; ++i) {
		objects.push_back(Ball(i, State::height));
		objects.push_back(Ball(i, 0));
	}

	for(int i = 0; i <= State::height; ++i){
		objects.push_back(Ball(State::width, i));
		objects.push_back(Ball(0, i));
	}
};
