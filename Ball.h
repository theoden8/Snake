#pragma once

#include <vector>

struct Ball {
	int x, y;
	Ball();
	Ball(int x, int y);
	Ball operator+ (const Ball &sec) const;
	bool operator== (const Ball &sec) const;
	bool operator!= (const Ball &sec) const;
	Ball operator- () const;
	Ball operator- (const Ball &sec) const;
	double degree () const;

	bool operator < (const Ball &sec) const;
};

bool FreeSpot(const Ball &spot, const std::vector <Ball> &obstacles);
