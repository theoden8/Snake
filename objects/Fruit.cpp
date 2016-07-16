#include <algorithm>

#include "Fruit.hpp"
#include "State.hpp"
#include "Common.hpp"
#include "Snake.hpp"

Fruit::Fruit(int fruantity):
	fruantity(fruantity)
{
	PushBack(fruantity);

	for(int i = 0; i < NO_ICONSETS; ++i)
		fruitsGallery[i].load(FOLDER + "_textures/" + std::to_string(i) + "_FRUIT.tga");
}

void Fruit::DeleteFruit(const Ball &fruit) {
	objects.erase(
		std::remove(
			objects.begin(),
			objects.end(),
			fruit
		),
		objects.end()
	);
}

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
	SSNAKE->PushBack();
	PushBack(1);
	++frufru;
}
