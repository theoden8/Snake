#include <cassert>

#include "Aimer.hpp"
#include "Functions.hpp"
#include "State.hpp"
#include "Snake.hpp"

const int Aimer::NO_AIMS = 5;

Aimer::Aimer(Snake *s):
	snake(s)
{}

const char *Aimer::Name() const {
	switch(aim) {
		case 0:
			return "None";
		case 1:
			return "Closest Fruit";
		case 2:
			return "Random fruit";
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


const std::map <Ball, bool> &Aimer::Sonar() {
	if(sonar.empty())
		Scan();

	return sonar;
}

void Aimer::SonarToggleHead() {
	const Ball &head = snake->head();
	if(sonar.count(head))
		sonar.erase(head);
	else
		sonar[head] = true;
}

std::map <Ball, int> &Aimer::DistancesHead() {
	if(distances_head.empty())
		distances_head = bfs(Sonar(), snake->head());

	return distances_head;
}

void Aimer::Scan() {
	for(const auto &objects : {WALLS->GetObjects(), snake->GetObjects()})
		for(const auto &obj : objects)
			sonar[obj] = true;

	const std::vector <Ball> &snobj = snake->GetObjects();
	std::map <Ball, int> &distances = DistancesHead();
	for(size_t i = 1; i < snobj.size(); ++i) {
		if(distances.count(snobj[i]) == 1
			&& distances.at(snobj[i]) > snobj.size() - i)
		{
			/* distances = bfs(Sonar(), snake->head()); */
			sonar.erase(snobj[i]);
		}
	}
}

void Aimer::Reset() {
	sonar.clear();
	distances_head.clear();
	target = UNDEF_BALL;
}


Ball Aimer::GetTarget() {
	assert(0 <= aim && aim < NO_AIMS);

	if(aim == 0) {
		target = UNDEF_BALL;
		return UNDEF_BALL;
	}

	if(target != UNDEF_BALL) {
		assert(target.is_valid_position());
		return target;
	}

	switch(aim) {
		case 1:
			SetTargetClosestFruit();
		break;
		case 2:
			SetTargetRandomFruit();
		break;
		case 3:
			SetTargetFurthestFruit();
		break;
		case 4:
			SetTargetSnakeTail();
		break;
	}

	assert(target.is_valid_position() || target == UNDEF_BALL);
	return target;
}

void Aimer::SetTargetClosestFruit() {
	if(FRUITS->GetObjects().empty())
		return;

	int range = UNDEF_INT;
	const std::map <Ball, int> &distances = DistancesHead();
	for(const auto &fruit : FRUITS->GetObjects()) {
		if(
			distances.count(fruit)
			&& (
				range == UNDEF_INT
				|| range > distances.at(fruit)
			)
		)
		{
			target = fruit;
			range = distances.at(target);
		}
	}
}

void Aimer::SetTargetRandomFruit() {
	const std::map <Ball, int> &distances = DistancesHead();

	if(
		Ball::InSegment(snake->targetLast, FRUITS->GetObjects())
		&& distances.count(snake->targetLast))
	{
		target = snake->targetLast;
		return;
	}
	target = FRUITS->GetObjects()[rand() % FRUITS->GetObjects().size()];
}

void Aimer::SetTargetFurthestFruit() {
	if(FRUITS->GetObjects().empty())
		return;

	const std::map <Ball, int> &distances = DistancesHead();
	int range = UNDEF_INT;
	if(
		Ball::InSegment(snake->targetLast, FRUITS->GetObjects())
		&& distances.count(snake->targetLast))
	{
		target = snake->targetLast;
		return;
	}
	for(const auto &fruit : FRUITS->GetObjects()) {
		if(distances.count(fruit) && range < distances.at(fruit)) {
			target = fruit;
			range = distances.at(target);
		}
	}
}

void Aimer::SetTargetSnakeTail() {
	const std::map <Ball, int> &distances = DistancesHead();
	int range = UNDEF_INT;
	target = snake->GetObjects().back();
	for(int i = snake->GetObjects().size() - 1; i >= 0; --i) {
		if(distances.count(target)) {
			target = snake->GetObjects()[i];
			range = distances.at(target);
			return;
		}
	}
}
