#include <cstdlib>

#include "Fruit.hpp"
#include "Functions.hpp"
#include "Graphics.hpp"
#include "State.hpp"
#include "Wall.hpp"
#include "Snake.hpp"

Fruit::Fruit(int fruantity):
	fruantity(fruantity)
{
	for(int i = 0; i < 8; ++i)
		fruitsGallery[i].load(State::folder + "_textures/" + std::to_string(i) + "_FRUIT.tga");
}

void Fruit::Push_Back(int new_fruantity) {
	for(int i = 0; i < new_fruantity; ++i) {
		if(fruitStorage.size() >= State::width * State::height - SNAKE->snake.size() - (WALLS->walls.size() >> 1) + 3) {
			return;
		}
		Ball new_fruit;
		do {
			new_fruit = Ball(
				rand() % (int(State::width) - 1) + 1,
				rand() % (int(State::height) - 1) + 1
			);
		} while (
			Ball::FreeSpot(new_fruit, WALLS->walls)
			|| Ball::FreeSpot(new_fruit, SNAKE->snake)
			|| Ball::FreeSpot(new_fruit, fruitStorage)
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


void Fruit::Keyboard(char key) {
	switch(key) {
		case 'm' :
			++(fru_delta = (fru_delta < 0) ? 0 : fru_delta);
			Push_Back((fru_delta >> 2) + 1);
			break;
		case 'n' :
			--(fru_delta = (fru_delta > 0) ? 0 : fru_delta);
			for(int i = 0; i < (abs(fru_delta) >> 2) + 1; ++i) {
				DeleteFruit(fruitStorage.front());
			}
			break;
	}
}

void Fruit::Display() {
	for(auto fruit : fruitStorage) {
		double degree = 90;
		Graphics::DrawObject(fruit.x, fruit.y, fruitsGallery[SNAKE->ID].id, degree);
	}
}
