#pragma once

#include <map>
#include <queue>
#include <string>

#include "Ball.hpp"

std::vector <Ball> GetSteps();
std::map <Ball, int> bfs(std::map <Ball, bool> &sonar, const Ball &from);
