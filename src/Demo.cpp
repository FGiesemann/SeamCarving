#include "Demo.h"
#include "SeamCarving.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

SeamCarvingDemo::SeamCarvingDemo(const std::string& inputPath) : inPath{ inputPath } {
    sAppName = "Seam Carving Demonstration";
}

bool SeamCarvingDemo::OnUserCreate() {
    inputImage = std::make_unique<olc::Sprite>(inPath);
    smallerImage = std::make_unique<olc::Sprite>(inputImage->width, inputImage->height);
    restoreOriginalImage();
    pixelCost.resize(inputImage->width * inputImage->height, 0);
    seamCost.resize(inputImage->width * inputImage->height, 0);

    updateSeamData();

    return true;
}

bool SeamCarvingDemo::OnUserUpdate(float fElapsedTime) {
    Clear(olc::BLACK);
    if (GetKey(olc::ESCAPE).bPressed)
        return false;
    if (GetKey(olc::MINUS).bPressed)
        removeSeam();
    if (GetKey(olc::SPACE).bHeld)
        removeSeam();
    if (GetKey(olc::D).bPressed)
        drawSeam = !drawSeam;
    if (GetKey(olc::I).bPressed)
        mode = DrawMode::Image;
    if (GetKey(olc::C).bPressed)
        mode = DrawMode::PixelCost;
    if (GetKey(olc::S).bPressed)
        mode = DrawMode::SeamCost;
    if (GetKey(olc::M).bPressed)
        mouseMode = !mouseMode;
    if (GetKey(olc::R).bPressed)
        restoreOriginalImage();

    auto drawRedPixel = [&](int x, int y) { Draw({ x, y }, olc::RED); };
    switch (mode) {
    case DrawMode::Image:
        DrawSprite({ 0, 0 }, smallerImage.get());
        break;
    case DrawMode::PixelCost:
        DrawCostImage(pixelCost);
        break;
    case DrawMode::SeamCost:
        DrawCostImage(seamCost);
        break;
    }
    if (drawSeam)
        traceMinimumSeam(drawRedPixel);
    return true;
}

void SeamCarvingDemo::updateSeamData() {
    computePixelCosts(smallerImage.get(), pixelCost);
    accumulateSeamCosts(smallerImage->width, smallerImage->height, pixelCost, seamCost);
}

void SeamCarvingDemo::removeSeam() {
    int w = smallerImage->width;
    int h = smallerImage->height;
    std::unique_ptr<olc::Sprite> newImage = std::make_unique<olc::Sprite>(w - 1, h);

    auto removePixelFromImageRow = [&](int x, int y) {
        std::copy(smallerImage->pColData.begin() + y * w, smallerImage->pColData.begin() + y * w + x, newImage->pColData.begin() + y * (w - 1));
        std::copy(smallerImage->pColData.begin() + y * w + x + 1, smallerImage->pColData.begin() + (y + 1) * w, newImage->pColData.begin() + y * (w - 1) + x);
    };

    traceMinimumSeam(removePixelFromImageRow);
    smallerImage = std::move(newImage);

    updateSeamData();
}

void SeamCarvingDemo::restoreOriginalImage() {
    smallerImage.reset(new olc::Sprite(inputImage->width, inputImage->height));
    std::copy(inputImage->pColData.begin(), inputImage->pColData.end(), smallerImage->pColData.begin());
}

void SeamCarvingDemo::DrawCostImage(const std::vector<int>& cost) {
    auto maxCost = *std::max_element(cost.begin(), cost.end());
    for (int y = 0; y < smallerImage->height; ++y) {
        for (int x = 0; x < smallerImage->width; ++x) {
            int value = int(float(cost[y * smallerImage->width + x]) / maxCost * 255.0f);
            Draw({ x, y }, olc::Pixel(value, value, value));
        }
    }
}

int SeamCarvingDemo::detectMinimumSeamCost() {
    if (mouseMode)
        return GetMouseX();

    int x_val = seamCost[(smallerImage->height - 1) * smallerImage->width];
    int min_x = 0;
    for (int x = 1; x < smallerImage->width; ++x) {
        int c = seamCost[(smallerImage->height - 1) * smallerImage->width + x];
        if (c < x_val) {
            min_x = x;
            x_val = c;
        }
    }
    return min_x;
}

void SeamCarvingDemo::traceMinimumSeam(std::function<void(int, int)> f) {
    int width = smallerImage->width;
    int x = detectMinimumSeamCost();
    int y = smallerImage->height - 1;

    f(x, y);
    while (y > 0) {
        int c = seamCost[y * width + x] - pixelCost[y * width + x];
        if ((x > 0) && seamCost[(y - 1) * width + (x - 1)] == c) {
            x = x - 1;
        } else if ((x < width - 1) && seamCost[(y - 1) * width + x] != c) {
            x = x + 1;
        }
        y = y - 1;
        f(x, y);
    }
}