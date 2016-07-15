#include <cstdlib>
#include <algorithm>

#include "Fruit.hpp"
#include "Graphics.hpp"
#include "State.hpp"
#include "Snake.hpp"

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
	for(const auto &fruit : objects) {
		double degree = 90;
		Graphics::DisplayObject(fruit, fruitsGallery[SSNAKE->ID].id, degree);
	}
}
