#include "Wall.hpp"
#include "Graphics.hpp"

void Wall::Display() {
	for(const auto &wall : objects) {
		double degree = 90;
		Graphics::DisplayObject(wall, wallsGallery[0].id, degree);
	}
}
