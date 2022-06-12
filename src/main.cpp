#include "Demo.h"

int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        std::cout << "Please provide an input image as the first parameter!\n";
        return 1;
    }
    SeamCarvingDemo demo(argv[1]);

    int windowWidth = 1000;
    int windowHeight = 800;
    if (argc > 2)
        windowWidth = std::stoi(argv[2]);
    if (argc > 3)
        windowHeight = std::stoi(argv[3]);

    if (demo.Construct(windowWidth, windowHeight, 1, 1))
        demo.Start();

    return 0;
}
