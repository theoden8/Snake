#include "Wall.hpp"
#include "Functions.hpp"
#include "Graphics.hpp"

Wall::Wall() {
	for(int i = 0; i <= 0; ++i)
		wallsGallery[i].load(State::folder + "_textures/" + std::to_string(i) + "_WALL.tga");

	for(int i = 0; i <= State::width; ++i) {
		walls.push_back(Ball(i, State::height));
		walls.push_back(Ball(i, 0));
	}

	for(int i = 0; i <= State::height; ++i){
		walls.push_back(Ball(State::width, i));
		walls.push_back(Ball(0, i));
	}
};


void Wall::Keyboard(char key) {
}

void Wall::Display() {
	for(auto wall : walls) {
		double degree = 90;
		Graphics::DrawObject(wall.x, wall.y, wallsGallery[0].id, degree);
	}
}
