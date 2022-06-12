#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class SeamCarving : public olc::PixelGameEngine
{
public:
	SeamCarving();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};
