#include "olcPixelGameEngine.h"

#include <vector>

void computePixelCosts(const olc::Sprite* image, std::vector<int>& cost);
void accumulateSeamCosts(int width, int height, const std::vector<int>& pixelCost, std::vector<int>& seamCost);
