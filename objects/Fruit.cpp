#include <cstdlib>

#include "Fruit.hpp"
#include "Wall.hpp"
#include "Snake.hpp"
#include "Functions.hpp"

Fruit::Fruit(std::string folder, int width, int height, int fruantity):
	width(width), height(height), fruantity(fruantity)
{
	for(int i = 0; i < 8; ++i) {
		fruitsGallery[i].load(folder + "_textures/" + std::to_string(i) + "_FRUIT.tga");
	}
}

void Fruit::Keyboard(char key) {
	switch(key) {
		case 'm' :
			++(fru_delta = (fru_delta < 0) ? 0 : fru_delta);
			frs_->Push_Back(wls_, sn_, (frs_->fru_delta >> 2) + 1);
			break;
		case 'n' :
			--(fru_delta = (fru_delta > 0) ? 0 : fru_delta);
			for(int i = 0; i < (abs(fru_delta) >> 2) + 1; ++i) {
				DeleteFruit(fruitStorage.front());
			}
			break;
	}
}

void Fruit::Push_Back(Wall *w, Snake *s, int new_fruantity) {
	for(int i = 0; i < new_fruantity; ++i) {
		if(fruitStorage.size() >= width * height - s->snake.size() - (w->walls.size() >> 1) + 3) {
			return;
		}
		Ball new_fruit;
		do {
			new_fruit = Ball(rand() % (width - 1) + 1, rand() % (height - 1) + 1);
		} while (
			FreeSpot(new_fruit, w->walls)
			|| FreeSpot(new_fruit, s->snake)
			|| FreeSpot(new_fruit, fruitStorage)
		);
		fruitStorage.push_back(new_fruit);
	}
}

void Fruit::DeleteFruit(const Ball &eated_fruit) {
	std::vector <Ball> new_fruitStorage;
	for(auto fruit : fruitStorage) {
		if(!(eated_fruit == fruit))
			new_fruitStorage.push_back(fruit);
	}
	fruitStorage = new_fruitStorage;
}
