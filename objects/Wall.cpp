#include "Wall.hpp"
#include "Functions.hpp"

Wall::Wall(std::string folder, int width, int height) {
	for(int i = 0; i <= 0; ++i) {
		cageGallery[i].load(folder + "_textures/" + std::to_string(i) + "_WALL.tga");
	}
	for(int i = 0; i <= width; ++i) {
		walls.push_back(Ball(i, height));
		walls.push_back(Ball(i, 0));
	}
	for(int i = 0; i <= height; ++i){
		walls.push_back(Ball(width, i));
		walls.push_back(Ball(0, i));
	}
};

void Wall::Keyboard (char key) {
}
