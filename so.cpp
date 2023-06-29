// main.cpp
// g++ -o so so.cpp -ldl
#include <iostream>
#include <fstream>
#include <dlfcn.h>

extern "C" {
    void drawRectangle(unsigned char* image, int width, int height, int x1, int y1, int x2, int y2, int borderWidth);
}

int main() {
    const int width = 2048;
    const int height = 1536;
    const int x1 = 50;
    const int y1 = 50;
    const int x2 = 1000;
    const int y2 = 1200;
    const int borderWidth = 4;

    // Load the shared object file
    void* handle = dlopen("./libdrawrectangle.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to load the shared object file: " << dlerror() << std::endl;
        return 1;
    }

    // Get the function pointer to drawRectangle
    typedef void (*DrawRectangleFunc)(unsigned char*, int, int, int, int, int, int, int);
    DrawRectangleFunc drawRectangleFunc = reinterpret_cast<DrawRectangleFunc>(dlsym(handle, "drawRectangle"));
    if (!drawRectangleFunc) {
        std::cerr << "Failed to find the drawRectangle function: " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    // Read the YUV image file
    std::ifstream inputFile("so-input.yuv", std::ios::binary);
    if (!inputFile) {
        std::cerr << "Failed to open the input YUV image file!" << std::endl;
        dlclose(handle);
        return 1;
    }

    // Calculate the image buffer size
    const int imageSize = width * height * 3 / 2;

    // Allocate memory for the image buffer
    unsigned char* imageBuffer = new unsigned char[imageSize];

    // Read the YUV image into the buffer
    inputFile.read(reinterpret_cast<char*>(imageBuffer), imageSize);

    // Close the input file
    inputFile.close();

    // Call the drawRectangle function
    drawRectangleFunc(imageBuffer, width, height, x1, y1, x2, y2, borderWidth);

    // Save the modified YUV image to a file
    std::ofstream outputFile("so-output.yuv", std::ios::binary);
    if (!outputFile) {
        std::cerr << "Failed to create the output YUV image file!" << std::endl;
        delete[] imageBuffer;
        dlclose(handle);
        return 1;
    }

    // Write the modified YUV image to the output file
    outputFile.write(reinterpret_cast<const char*>(imageBuffer), imageSize);

    // Close the output file
    outputFile.close();

    // Clean up
    delete[] imageBuffer;
    dlclose(handle);

    return 0;
}
