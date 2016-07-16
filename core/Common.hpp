#pragma once

#include <string>
#include <map>

#define WALLS  Common::walls
#define FRUITS Common::fruits
#define SNAKE  Common::snake

#define SSNAKE ((Snake *)SNAKE)
#define FFRUITS ((Fruit *)FRUITS)

class Object;

struct Common {
	static Object
		*walls,
		*fruits,
		*snake;

	static void Init(const int argc, char **argv);
	static void Display();
	static void Timer();
};
