#pragma once

#include <string>
#include <map>

class Wall;
class Fruit;
class Snake;

#define WALLS  State::walls
#define FRUITS State::fruits
#define SNAKE  State::snake

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

	static Wall *walls;
	static Fruit *fruits;
	static Snake *snake;

	static void InitState(const int &argc, char **argv);
	static void Keyboard(char key);
	static void Display();
};
