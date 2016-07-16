#include "Aimer.hpp"
#include "Functions.hpp"
#include "State.hpp"
#include "Snake.hpp"

#include <iostream>

const int Aimer::NO_AIMS = 4;

Aimer::Aimer(Snake *s):
	snake(s)
{}

const char *Aimer::GetName() const {
	switch(aim) {
		case 0:
			return "Hand Brake";
		case 1:
			return "Closest Fruit";
		case 2:
			return "Newest fruit";
		case 3:
			return "Furthest fruit";
		case 4:
			return "Tail";
		default:
			return NULL;
	}
}

const Snake *Aimer::GetSnake() const {
	return snake;
}

const std::map <Ball, bool> &Aimer::GetSonar() {
	if(sonar.empty())
		Scan();
	return sonar;
}

void Aimer::Scan() {
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
}

void Aimer::Reset() {
	sonar.clear();
}


void Aimer::SetTarget(Ball &target) {
	std::cout << "aimer: aim " << aim << std::endl;
	switch(aim) {
		case 0:
			target = snake->GetObjects().front() + snake->currentDirection;
		break;
		case 1:
			/* SetTargetClosestFruit(target); */
			SetTargetNewestFruit(target);
		break;
		case 2:
			SetTargetNewestFruit(target);
		break;
		case 3:
			SetTargetFurthestFruit(target);
		break;
		case 4:
			SetTargetSnakeTail(target);
		break;
	}
	std::cout << "aimer: target " << target << std::endl;
}

void Aimer::SetTargetClosestFruit(Ball &target) {
	std::cout << "setsonar" << std::endl;
	std::map <Ball, int> way_to = bfs(GetSonar(), snake->GetObjects().front());
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
	std::map <Ball, int> way_to = bfs(GetSonar(), snake->GetObjects().front());
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
	std::map <Ball, int> way_to = bfs(GetSonar(), snake->GetObjects().front());
	for(int i = snake->GetObjects().size() - 1; i >= 0; --i) {
		if(way_to.count(target)) {
			target = snake->GetObjects()[i];
			range = way_to[target];
			return;
		}
	}
}
