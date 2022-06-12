#include "SeamCarving.h"

namespace {

int absPixelDiff(const olc::Pixel& p, const olc::Pixel& q) {
    return std::abs(p.r - q.r) + std::abs(p.g - q.g) + std::abs(p.b - q.b);
}

int computePixelCost(const olc::Sprite* image, int x, int y) {
    olc::Pixel p = image->GetPixel({ x, y });

    int dx = 0;
    if (x > 0)
        dx += absPixelDiff(p, image->GetPixel({ x - 1, y }));
    if (x < image->width - 1)
        dx += absPixelDiff(p, image->GetPixel({ x + 1, y }));

    int dy = 0;
    if (y > 0)
        dy += absPixelDiff(p, image->GetPixel({ x, y - 1 }));
    if (dy < image->height - 1)
        dy += absPixelDiff(p, image->GetPixel({ x, y + 1 }));

    return dx + dy;
}

}

void computePixelCosts(const olc::Sprite* image, std::vector<int>& cost) {
    const int width = image->width;
    for (int y = 0; y < image->height; ++y) {
        for (int x = 0; x < width; ++x) {
            cost[y * width + x] = computePixelCost(image, x, y);
        }
    }
}

void accumulateSeamCosts(int width, int height, const std::vector<int>& pixelCost, std::vector<int>& seamCost) {
    for (int x = 0; x < width; ++x)
        seamCost[x] = pixelCost[x];

    for (int y = 1; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int aboveSeamCost = seamCost[(y - 1) * width + x];
            int cost_l = pixelCost[y * width + x] + ((x > 0) ? seamCost[(y - 1) * width + (x - 1)] : 2 * aboveSeamCost);
            int cost_u = pixelCost[y * width + x] + aboveSeamCost;
            int cost_r = pixelCost[y * width + x] + ((x < width - 1) ? seamCost[(y - 1) * width + (x + 1)] : 2 * aboveSeamCost);

            seamCost[y * width + x] = std::min(cost_l, std::min(cost_u, cost_r));
        }
    }
}
