#pragma once

#include <vector>
#include <map>

#include "Ball.hpp"

std::vector <Ball> GetSteps();
std::map <Ball, int> bfs(const std::map <Ball, bool> &sonar, const Ball &from);
