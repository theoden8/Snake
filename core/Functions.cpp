#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include "Functions.hpp"

std::vector <Ball> GetSteps() {
	return {
		Ball(-1, 0),
		Ball(0, 1),
		Ball(0, -1),
		Ball(1, 0),
	};
}

std::map <Ball, int> bfs(std::map <Ball, bool> &sonar, const Ball &from) {
	std::queue <Ball> spiral;
	std::map <Ball, int>  way_to;
	spiral.push(from);
	way_to[from] = 0;
	while (!spiral.empty()) {
		Ball pointer = spiral.front();
		spiral.pop();
		for (auto it : GetSteps()) {
			Ball movv = pointer + it;
			if(sonar.count(movv) == 0 && (way_to.count(movv) == 0)) {
				way_to[movv] = way_to[pointer] + 1;
				spiral.push(movv);
			}
		}
	}
	return way_to;
}
