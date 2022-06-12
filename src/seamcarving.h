#include "olcPixelGameEngine.h"

class SeamCarving : public olc::PixelGameEngine
{
public:
	SeamCarving() {
		sAppName = "Seam Carving";
	}

public:
	bool OnUserCreate() override {
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));
		return true;
	}
};