#pragma once

#include <vector>
#include <string>

#include "Object.hpp"
#include "Image.hpp"

class Fruit : public Object {
	Image fruitsGallery[8];

public:
	int
		fruantity,	//	number of fruits on the arena
		fru_delta = 0,
		frufru = 0;

public:
	Fruit(int fruantity);
	void PushBack(int new_fruantity);
	void DeleteFruit(const Ball &sH);

	void Keyboard(char key);
	void Display();
};
