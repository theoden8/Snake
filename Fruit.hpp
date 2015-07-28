#pragma once

#include <vector>
#include <string>

#include "Imagg.hpp"
#include "Ball.hpp"

struct Walls;
struct Snakes;

struct Fruits {
	Imagg fruitsGallery[8];
	std::vector <Ball> fruit_Storage;
	int width, height,
	    fruantity,	//	number of fruits on field
	    fru_delta,	//	how many fruits are created with appropriate button
	    frufru;	//	number of fruits eaten

	Fruits(std::string folder, int width, int height, int fruantity);
	void Keyboard		(char key);
	void Push_Back		(Walls *c, Snakes *s, int new_fruantity);
	void DeleteFruit	(const Ball &sH);
};
