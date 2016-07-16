#include <cstdlib>
#include <ctime>

#include "Graphics.hpp"

int main(int argc, char **argv) {
	srand(time(NULL));
	Graphics::Init(argc, argv);
}
