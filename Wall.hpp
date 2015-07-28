#pragma once

#include <vector>
#include <string>

#include "Imagg.hpp"
#include "Ball.hpp"

struct Walls {
	Imagg cageGallery[0];
	std::vector <Ball> walls;
	Walls(std::string folder, int width, int height);
	void Keyboard(char key);
};
