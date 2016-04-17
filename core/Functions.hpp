#pragma once

#include <map>
#include <queue>
#include <string>

#include "Ball.hpp"
#include "Snake.hpp"
#include "Wall.hpp"
#include "Fruit.hpp"

std::map <unsigned char, Ball> GetSteps();
std::map <Ball, int> bfs(std::map <Ball, bool> &sonar, const Ball &from);
bool process_key(const char *keys, const char key);
