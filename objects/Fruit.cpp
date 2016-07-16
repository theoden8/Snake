#include <algorithm>

#include "Fruit.hpp"
#include "State.hpp"

Fruit::Fruit(int fruantity):
	fruantity(fruantity)
{
	for(int i = 0; i < 8; ++i)
		fruitsGallery[i].load(FOLDER + "_textures/" + std::to_string(i) + "_FRUIT.tga");
}

void Fruit::DeleteFruit(const Ball &fruit) {
	objects.erase(
		std::remove(
			objects.begin(),
			objects.end(),
			fruit
		),
		objects.end()
	);
}
