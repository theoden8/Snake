#include <cstdlib>

#include "Fruit.h"
#include "Wall.h"
#include "Snake.h"
#include "Functions.h"

Fruits::Fruits(std::string folder, int width, int height, int fruantity):
	width(width), height(height), fruantity(fruantity), fru_delta(0), frufru(0)
{
	for(int i = 0; i < 8; ++i) {
		fruitsGallery[i].load(folder + "textures/" + str(i) + "_FRUIT.tga");
	}
}

void Fruits::Keyboard(char key) {
	switch(key) {
		case 'm' :
			if(fru_delta < 0) {
				fru_delta = 0;
			}
			++fru_delta;
			break;
		case 'n' :
			if(fru_delta > 0) {
				fru_delta = 0;
			}
			--fru_delta;
			for(int i = 0; i < (abs(fru_delta) >> 2) + 1; ++i) {
				DeleteFruit(fruit_Storage.front());
			}
			break;
	}
}

void Fruits::Push_Back (Walls *w, Snakes *s, int new_fruantity) {
	for(int i = 0; i < new_fruantity; ++i) {
		if(fruit_Storage.size() >= width * height - s->snake.size() - (w->walls.size() >> 1) + 3) {
			return;
		}
		Ball new_fruit;
		do {
			new_fruit = Ball(rand() % (width - 1) + 1, rand() % (height - 1) + 1);
		} while (
			FreeSpot(new_fruit, w->walls)
			|| FreeSpot(new_fruit, s->snake)
			|| FreeSpot(new_fruit, fruit_Storage)
		);
		fruit_Storage.push_back(new_fruit);
	}
}

void Fruits::DeleteFruit (const Ball &eated_fruit) {
	std::vector <Ball> new_fruit_Storage;
	for(auto fruit : fruit_Storage) {
		if (!(eated_fruit == fruit)) {
			new_fruit_Storage.push_back(fruit);
		}
	}
	fruit_Storage = new_fruit_Storage;
}
