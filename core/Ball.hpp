#pragma once

#include <ostream>
#include <vector>

struct Ball {
	int x, y;
	Ball();
	Ball(int x, int y);
	Ball operator+ (const Ball &sec) const;
	void operator+=(const Ball &sec);
	bool operator== (const Ball &sec) const;
	bool operator!= (const Ball &sec) const;
	Ball operator-() const;
	Ball operator-(const Ball &sec) const;
	bool operator< (const Ball &sec) const;
	double degree() const;
	const bool is_valid_step() const;
	const bool is_valid_position() const;

	friend std::ostream &operator<< (std::ostream &os, const Ball &B);

	static bool InSegment(const Ball &spot, const std::vector <Ball> &objects);
	static bool InSegment(const Ball &spot, const std::vector <Ball> &objects, const Ball &interval);

};
