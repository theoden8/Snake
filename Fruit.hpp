#pragma once

#include <vector>
#include <string>

#include "State.hpp"
#include "Object.hpp"

class Fruit : public Object {
	Image fruitsGallery[NO_ICONSETS];

public:
	int
		fruantity,	//	number of fruits on the arena
		fru_delta = 0,
		frufru = 0;

public:
	Fruit(int fruantity);
	void PushBack(int new_fruantity);
	void EatFruit();
	void DeleteFruit(const Ball &sH);

	void Keyboard(char key);
	void Display();
};
