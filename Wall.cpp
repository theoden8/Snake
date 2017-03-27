#include "Wall.hpp"
#include "State.hpp"
#include "Graphics.hpp"

#include <iostream>

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


void Wall::Display() {
	for(const auto &wall : objects) {
		double degree = 90;
		Graphics::DisplayObject(wall, wallsGallery[0].id, degree);
	}
}
