#include <cstdlib>

#include "Graphics.hpp"
#include "State.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"

#include "Common.hpp"

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
		Graphics::DisplayObject(fruit, fruitsGallery[SSNAKE->ID].id, degree);
	}
}
