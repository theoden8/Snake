#include <math.h>

#include "Ball.hpp"

Ball::Ball()
{
}

Ball::Ball(int x, int y):
	x(x), y(y)
{
}

Ball Ball::operator+ (const Ball &sec) const {
	return Ball(x + sec.x, y + sec.y);
}

bool Ball::operator== (const Ball &sec) const {
	return (x == sec.x) && (y == sec.y);
}

bool Ball::operator!= (const Ball &sec) const {
	return !(*this == sec);
}

Ball Ball::operator- () const {
	return Ball(-x, -y);
}

Ball Ball::operator- (const Ball &sec) const {
	return Ball(x - sec.x, y - sec.y);
}


double Ball::degree () const {
	return atan2(y, x) / M_PI * 180;
}

bool Ball::operator < (const Ball &sec) const {
	return (x != sec.x) ? (x < sec.x) : (y < sec.y);
}

bool FreeSpot(const Ball &spot, const std::vector <Ball> &obstacles) {
	for (int i = 0; i < obstacles.size(); ++i) {
		if(spot == obstacles[i] && &spot != &obstacles[i]) {
			return 1;
		}
	}
	return 0;
}
