#include <cstdlib>
#include <cmath>

/* #include <iostream> */
#include <queue>

#include "Functions.hpp"

std::vector <Ball> GetSteps() {
	return {
		Ball(-1, 0),
		Ball(0, 1),
		Ball(0, -1),
		Ball(1, 0),
	};
}

std::map <Ball, int> bfs(const std::map <Ball, bool> &sonar, const Ball &from) {
	std::queue <Ball> spiral;
	std::map <Ball, int>  way_to;
	spiral.push(Ball(from));
	way_to[from] = 0;
	while (!spiral.empty()) {
		Ball pointer = spiral.front();
		spiral.pop();
		for(const auto &step : GetSteps()) {
			Ball move = pointer + step;
			if(sonar.count(move) == 0 && (way_to.count(move) == 0)) {
				way_to[move] = way_to[pointer] + 1;
				spiral.push(move);
			}
		}
	}
	return way_to;
}
