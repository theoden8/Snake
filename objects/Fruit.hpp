#pragma once

#include <vector>
#include <string>

#include "Image.hpp"
#include "Ball.hpp"

struct Wall;
struct Snake;

struct Fruit {
	Image fruitsGallery[8];
	std::vector <Ball> fruitStorage;
	int
		width,
		height,
		fruantity,	//	number of fruits on field
		fru_delta = 0,
		frufru = 0;

	Fruit(std::string folder, int width, int height, int fruantity);
	void Keyboard(char key);
	void Push_Back(Wall *c, Snake *s, int new_fruantity);
	void DeleteFruit(const Ball &sH);
};
