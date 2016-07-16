#include "Aimer.hpp"
#include "Functions.hpp"
#include "Object.hpp"
#include "Common.hpp"
#include "Snake.hpp"

#include <iostream>
void Aimer::SetSonar() {
	for(const auto &objects : {WALLS->GetObjects(), snake->GetObjects()})
		for(const auto &obj : objects)
			sonar[obj] = true;

	std::cout << "way_to bfs" << std::endl;

	Ball &from = snake->GetObjects().front();
	std::map <Ball, int> way_to = bfs(sonar, from);

	std::cout << "bfs" << std::endl;

	const std::vector <Ball> &snobj = snake->GetObjects();
	for(size_t i = 1; i < snobj.size(); ++i) {
		if(way_to[snobj[i]] > snobj.size() - i) {
			std::cout << "sonar_erasing:: " << snobj[i] << std::endl;
			sonar.erase(snobj[i]);
		}
	}

	sonar.erase(snake->GetObjects().back());
	range = INVALID_INT;
	way_to = bfs(sonar, snake->GetObjects().front());
}


void Aimer::SetTarget(Ball &target) {
	std::cout << "aimer: aim " << aim << std::endl;
	switch(aim) {
		case 0:
			target = snake->GetObjects().front() + snake->currentDirection;
		break;
		case 1:
			/* SetTargetClosestFruit(target); */
			SetSonar();
			SetTargetNewestFruit(target);
		break;
		case 2:
			SetSonar();
			SetTargetNewestFruit(target);
		break;
		case 3:
			SetSonar();
			SetTargetFurthestFruit(target);
		break;
		case 4:
			SetSonar();
			SetTargetSnakeTail(target);
		break;
	}
	std::cout << "aimer: target " << target << std::endl;
}

void Aimer::SetTargetClosestFruit(Ball &target) {
	std::cout << "setsonar" << std::endl;
	for(const auto &fruit : FRUITS->GetObjects()) {
		if(way_to.count(fruit)) {
			if(range < way_to[fruit]) {
				target = fruit;
				range = way_to[target];
			}
		}
	}
	std::cout << target << std::endl;
}

void Aimer::SetTargetNewestFruit(Ball &target) {
	target = FRUITS->GetObjects().back();
}

void Aimer::SetTargetFurthestFruit(Ball &target) {
	for(const auto &fruit : FRUITS->GetObjects()) {
		if(way_to.count(fruit)) {
			if(
				range == INVALID_INT
				|| range > way_to[fruit]
			)
			{
				target = fruit;
				range = way_to[target];
			}
		}
	}
}

void Aimer::SetTargetSnakeTail(Ball &target) {
	target = snake->GetObjects().back();
	for(int i = snake->GetObjects().size() - 1; i >= 0; --i) {
		if(way_to.count(target)) {
			target = snake->GetObjects()[i];
			range = way_to[target];
			return;
		}
	}
}
