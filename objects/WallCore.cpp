#include "Wall.hpp"
#include "State.hpp"

Wall::Wall() {
	for(int i = 0; i <= 0; ++i)
		wallsGallery[i].load(FOLDER + "_textures/" + std::to_string(i) + "_WALL.tga");

	for(int i = 0; i <= WIDTH; ++i) {
		objects.push_back(Ball(i, HEIGHT));
		objects.push_back(Ball(i, 0));
	}

	for(int i = 0; i <= HEIGHT; ++i){
		objects.push_back(Ball(WIDTH, i));
		objects.push_back(Ball(0, i));
	}
};
