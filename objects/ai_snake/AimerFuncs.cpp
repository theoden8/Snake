#include "Aimer.hpp"
#include "Functions.hpp"
#include "Object.hpp"
#include "Common.hpp"

void Aimer::SetSonar(Ball &target) {
	for(const auto &obst : {WALLS->GetObjects(), SNAKE->GetObjects()})
		for(const auto &ball : obst)
			sonar[ball] = true;

	Ball &from = SNAKE->GetObjects().front();
	std::map <Ball, int> way_to = bfs(sonar, from);
	for(int i = 1; i < SNAKE->GetObjects().size(); ++i) {
		if(way_to[SNAKE->GetObjects()[i]] > SNAKE->GetObjects().size() - i)
			sonar.erase(SNAKE->GetObjects()[i]);
	}

	sonar.erase(SNAKE->GetObjects().back());
	range = INVALID_INT;
	way_to = bfs(sonar, SNAKE->GetObjects().front());
}


#include <iostream>
void Aimer::SetTarget(Ball &target) {
	std::cout << "aimer: target " << target << " aim " << aim << std::endl;
	switch(aim) {
		case 0:
			;
		break;
		case 1:
			SetTargetClosest(target);
		break;
		case 2:
			SetTargetNewest(target);
		break;
		case 3:
			SetTargetFurthest(target);
		break;
		case 4:
			SetTargetSnakeTail(target);
		break;
		default:
			return;
	}
}

void Aimer::SetTargetFurthest(Ball &target) {
	SetSonar(target);
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

void Aimer::SetTargetClosest(Ball &target) {
	SetSonar(target);
	for(const auto &fruit : FRUITS->GetObjects()) {
		if(way_to.count(fruit)) {
			if(range < way_to[fruit]) {
				target = fruit;
				range = way_to[target];
			}
		}
	}
}

void Aimer::SetTargetNewest(Ball &target) {
	target = FRUITS->GetObjects().back();
}

void Aimer::SetTargetSnakeTail(Ball &target) {
	SetSonar(target);
	target = SNAKE->GetObjects().back();
	for(int i = SNAKE->GetObjects().size() - 1; i >= 0; --i) {
		if(way_to.count(target)) {
			target = SNAKE->GetObjects()[i];
			range = way_to[target];
			return;
		}
	}
}
