#pragma once

#include <vector>
#include <string>

#include "Image.hpp"
#include "Ball.hpp"

class Fruit {
	Image fruitsGallery[8];
public:
	std::vector <Ball> fruitStorage;
	int
		fruantity,	//	number of fruits on the arena
		fru_delta = 0,
		frufru = 0;

	Fruit(int fruantity);
	void Push_Back(int new_fruantity);
	void DeleteFruit(const Ball &sH);

	void Keyboard(char key);
	void Display();
};
