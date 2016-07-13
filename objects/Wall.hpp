#pragma once

#include <vector>
#include <string>

#include "Image.hpp"
#include "Ball.hpp"

class Wall {
	Image wallsGallery[0];
public:
	std::vector <Ball> walls;
	Wall();

	void Keyboard(char key);
	void Display();
};
