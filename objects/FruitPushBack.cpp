#include <cstdlib>

#include "Fruit.hpp"
#include "State.hpp"
#include "Snake.hpp"
#include "Common.hpp"

void Fruit::PushBack(int new_fruantity) {
	for(int i = 0; i < new_fruantity; ++i) {
		if(objects.size() >= WIDTH * HEIGHT - SNAKE->GetObjects().size() - (WALLS->GetObjects().size() >> 1) + 3)
			return;

		Ball new_fruit;
		do {
			new_fruit = Ball(
				rand() % (int(WIDTH) - 1) + 1,
				rand() % (int(HEIGHT) - 1) + 1
			);
		} while (
			Ball::InSegment(new_fruit, WALLS->GetObjects())
			|| Ball::InSegment(new_fruit, SNAKE->GetObjects())
			|| Ball::InSegment(new_fruit, GetObjects())
		);
		objects.push_back(new_fruit);
	}
}

void Fruit::EatFruit() {
	DeleteFruit(SNAKE->GetObjects().front());
	PushBack(1);
	SSNAKE->PushBack();
	++frufru;
}
