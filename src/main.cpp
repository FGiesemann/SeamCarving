#include "seamcarving.h"

int main() {
	SeamCarving demo;
	if (demo.Construct(640, 480, 1, 1))
		demo.Start();

	return 0;
}
