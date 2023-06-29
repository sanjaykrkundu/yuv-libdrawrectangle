// drawrectangle.cpp
// g++ -shared -fPIC -o libdrawrectangle.so drawrectangle.cpp
extern "C" {
    void drawRectangle(unsigned char* image, int width, int height, int x1, int y1, int x2, int y2, int borderWidth) {
        // Draw rectangle border
        for (int y = y1; y <= y2; ++y) {
            for (int b = 0; b < borderWidth; ++b) {
                image[y * width + (x1 + b)] = 0; // Y component
                image[width * height + (y / 2) * (width / 2) + ((x1 + b) / 2)] = 128; // U component
                image[width * height + width * height / 4 + (y / 2) * (width / 2) + ((x1 + b) / 2)] = 128; // V component

                image[y * width + (x2 - b)] = 0; // Y component
                image[width * height + (y / 2) * (width / 2) + ((x2 - b) / 2)] = 128; // U component
                image[width * height + width * height / 4 + (y / 2) * (width / 2) + ((x2 - b) / 2)] = 128; // V component
            }
        }

        for (int x = x1; x <= x2; ++x) {
            for (int b = 0; b < borderWidth; ++b) {
                image[(y1 + b) * width + x] = 0; // Y component
                image[width * height + (y1 / 2 + b / 2) * (width / 2) + (x / 2)] = 128; // U component
                image[width * height + width * height / 4 + (y1 / 2 + b / 2) * (width / 2) + (x / 2)] = 128; // V component

                image[(y2 - b) * width + x] = 0; // Y component
                image[width * height + ((y2 - b) / 2) * (width / 2) + (x / 2)] = 128; // U component
                image[width * height + width * height / 4 + ((y2 - b) / 2) * (width / 2) + (x / 2)] = 128; // V component
            }
        }
    }
}
