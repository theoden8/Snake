#pragma once

#include <string>
#include <map>

#define WALLS  State::walls
#define FRUITS State::fruits
#define SNAKE  State::snake

#define SSNAKE ((Snake *)SNAKE)
#define FFRUITS ((Fruit *)FRUITS)

class Object;

struct State {
	static std::string
		folder;

	static bool
		pause,
		running;

	static double
		width,
		height,
		x_Display,
		y_Display;

	static int
		latency,
		latency_delta;

	static Object *walls;
	static Object *fruits;
	static Object *snake;

	static void InitState(const int &argc, char **argv);
	static void InitStateFin(const int argc, char **argv);
	static void Keyboard(char key);
	static void Display();
};
