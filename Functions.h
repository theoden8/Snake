#pragma once

#include <map>
#include <queue>
#include <string>

#include "Ball.h"
#include "Snake.h"
#include "Wall.h"
#include "Fruit.h"

std::map <unsigned char, Ball> GetSteps();
std::map <Ball, int> bfs(std::map <Ball, bool> &sonar, const Ball &from);
bool process_key(std::string keys, char key);
std::string str(unsigned int x);
