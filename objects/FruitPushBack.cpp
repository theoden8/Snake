#include <cstdlib>

#include "Fruit.hpp"
#include "State.hpp"

void Fruit::PushBack(int new_fruantity) {
	for(int i = 0; i < new_fruantity; ++i) {
		if(objects.size() >= State::width * State::height - SNAKE->GetObjects().size() - (WALLS->GetObjects().size() >> 1) + 3)
			return;

		Ball new_fruit;
		do {
			new_fruit = Ball(
				rand() % (int(State::width) - 1) + 1,
				rand() % (int(State::height) - 1) + 1
			);
		} while (
			Ball::FreeSpot(new_fruit, WALLS->GetObjects())
			|| Ball::FreeSpot(new_fruit, SNAKE->GetObjects())
			|| Ball::FreeSpot(new_fruit, GetObjects())
		);
		objects.push_back(new_fruit);
	}
}
