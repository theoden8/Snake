#include <math.h>

#include "Ball.hpp"

Ball::Ball()
{}

Ball::Ball(int x, int y):
	x(x), y(y)
{}

Ball Ball::operator+ (const Ball &sec) const {
	return Ball(x + sec.x, y + sec.y);
}

void Ball::operator+=(const Ball &sec) {
	this->x += sec.x;
	this->y += sec.y;
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

bool Ball::operator< (const Ball &sec) const {
	return (x != sec.x) ? (x < sec.x) : (y < sec.y);
}

double Ball::degree() const {
	return atan2(y, x) / M_PI * 180;
}


std::ostream &operator<< (std::ostream &os, const Ball &B) {
	os << '(' << B.x << ", " << B.y << ')';
	return os;
}

bool Ball::InSegment(const Ball &spot, const std::vector <Ball> &objects) {
	return InSegment(spot, objects, Ball(0, objects.size()));
}

bool Ball::InSegment(const Ball &spot, const std::vector <Ball> &objects, const Ball &interval) {
	for(size_t i = interval.x; i < interval.y; ++i)
		if(spot == objects[i])
			return 1;
	return 0;
}
