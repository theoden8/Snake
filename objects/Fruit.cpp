#include <cstdlib>

#include "Fruit.hpp"
#include "Wall.hpp"
#include "Snake.hpp"
#include "Functions.hpp"

Fruit::Fruit(std::string folder, int width, int height, int fruantity):
	width(width), height(height), fruantity(fruantity), fru_delta(0), frufru(0)
{
	for(int i = 0; i < 8; ++i) {
		fruitsGallery[i].load(folder + "_textures/" + std::to_string(i) + "_FRUIT.tga");
	}
}

void Fruit::Keyboard(char key) {
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

void Fruit::Push_Back (Wall *w, Snake *s, int new_fruantity) {
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

void Fruit::DeleteFruit (const Ball &eated_fruit) {
	std::vector <Ball> new_fruit_Storage;
	for(auto fruit : fruit_Storage) {
		if (!(eated_fruit == fruit)) {
			new_fruit_Storage.push_back(fruit);
		}
	}
	fruit_Storage = new_fruit_Storage;
}
