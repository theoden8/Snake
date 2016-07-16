#pragma once

#include <string>

#include "Ball.hpp"

class Object;

#define WIDTH State::width
#define HEIGHT State::height

#define FOLDER State::folder
#define NO_ICONSETS 8

#define WALLS  State::walls
#define FRUITS State::fruits
#define SNAKE  State::snake

#define SSNAKE ((Snake *)SNAKE)
#define FFRUITS ((Fruit *)FRUITS)

class State {
	static int
		latency_delta;

	static bool
		pause,
		running;
public:
	static int
		latency,
		skin_id;

	static std::string
		folder;

	static double
		width,
		height,
		x_Display,
		y_Display;

	static Object
		*walls,
		*fruits,
		*snake;

public:
	static void Init(const int &argc, char **argv);
	static void Keyboard(char key);
	static void Display();
	static void Timer();
};
