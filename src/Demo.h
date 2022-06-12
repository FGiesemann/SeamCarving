#include "olcPixelGameEngine.h"

class SeamCarvingDemo : public olc::PixelGameEngine {
public:
    SeamCarvingDemo(const std::string& inputPath);

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

private:
    std::string inPath;
    enum class DrawMode {
        Image, PixelCost, SeamCost
    };
    DrawMode mode = DrawMode::Image;
    bool drawSeam = false;
    bool mouseMode = false;

    std::unique_ptr<olc::Sprite> inputImage;
    std::unique_ptr<olc::Sprite> smallerImage;

    std::vector<int> pixelCost;
    std::vector<int> seamCost;

    void DrawCostImage(const std::vector<int>& cost);

    void restoreOriginalImage();
    void updateSeamData();
    int detectMinimumSeamCost();
    void traceMinimumSeam(std::function<void(int, int)> f);
    void removeSeam();
};
