#include <algorithm>

#include "Fruit.hpp"
#include "State.hpp"
#include "Snake.hpp"
#include "Graphics.hpp"

Fruit::Fruit(int fruantity):
	fruantity(fruantity)
{
	PushBack(fruantity);

	for(int i = 0; i < NO_ICONSETS; ++i)
		fruitsGallery[i].load(FOLDER + "textures/" + std::to_string(i) + "_FRUIT.tga");
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


void Fruit::Keyboard(char key) {
	switch(key) {
		case 'm' :
			++(fru_delta = (fru_delta < 0) ? 0 : fru_delta);
			PushBack((fru_delta >> 2) + 1);
			break;
		case 'n' :
			--(fru_delta = (fru_delta > 0) ? 0 : fru_delta);
			for(int i = 0; i < (abs(fru_delta) >> 2) + 1; ++i) {
				DeleteFruit(objects.front());
			}
			break;
	}
}

void Fruit::Display() {
	char text[20];

	glColor3f(0.3f, 1.0f, 0.0f);
	sprintf(text, "Points: %d..", frufru);
	Graphics::DisplayText(WIDTH + 1, HEIGHT * 0.97, text);

	glColor3f(1.0f, 0.0f, 0.0f);
	sprintf(text, "Fruits: %lu", objects.size());
	Graphics::DisplayText(WIDTH + 1, HEIGHT * 0.93, text);

	for(const auto &fruit : objects) {
		double degree = 90;
		Graphics::DisplayObject(fruit, fruitsGallery[State::skin_id].id, degree);
	}
}
