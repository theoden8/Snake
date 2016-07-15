#include "Snake.hpp"
#include "Aimer.hpp"
#include "Router.hpp"


void Snake::AutomaticMove() {
	Ball
		target,
		point;
	aimer->SetTarget(target);
	router->SetPoint(objects.front(), point, target);
	AutoCorrection(point);
}

/* void Snake::AutoCD_C() { */
/* 	std::map <Ball, bool> sonar; */
/* 		AddObstacle(sonar, WALLS->objects); */
/* 		AddObstacle(sonar, snake); */
/* 		DeleteSnakeObstacles(sonar, snake.front()); */
/* 	int MAX = 0, FRUIT = 1e9; */
/* 	Ball point = currentDirection; */
/* 	for(const auto &it_step : GetSteps()) { */
/* 		Ball movv = snake.front() + it_step; */
/* 		if(sonar.count(movv) == 0) { */
/* 			std::map <Ball, int> way_to = bfs(sonar, movv); */
/* 			int NEW_MAX = way_to.size(); */
/* 			if(NEW_MAX >= MAX) { */
/* 				if(NEW_MAX > MAX) { */
/* 					FRUIT = 1e9; */
/* 					point = it_step; */
/* 				} */
/* 				MAX = NEW_MAX; */
/* 				for(const auto &it_fruit : FRUITS->objects) { */
/* 					if(way_to.count(it_fruit) > 0) { */
/* 						int NEW_FRUIT = way_to[it_fruit]; */
/* 						if(NEW_FRUIT < FRUIT) { */
/* 							FRUIT = NEW_FRUIT; */
/* 							point = it_step; */
/* 						} */
/* 					} */
/* 				} */
/* 			} */
/* 		} */
/* 	} */
/* 	SetStep(point); */
/* } */
