#include <iostream>
#include <fstream>

void drawRectangle(unsigned char* yImage, unsigned char* uvImage, int width, int height, int x1, int y1, int x2, int y2, int borderWidth, unsigned char yColor, unsigned char uColor, unsigned char vColor) {
        // Draw Y component rectangle border
        for (int y = y1; y <= y2; ++y) {
            for (int b = 0; b < borderWidth; ++b) {
                yImage[y * width + (x1 + b)] = yColor;

                yImage[y * width + (x2 - b)] = yColor;
            }
        }

        for (int x = x1; x <= x2; ++x) {
            for (int b = 0; b < borderWidth; ++b) {
                yImage[(y1 + b) * width + x] = yColor;

                yImage[(y2 - b) * width + x] = yColor;
            }
        }

        // Draw UV component rectangle border
        x1 /= 2; // UV coordinates are half of Y coordinates
        x2 /= 2;
        y1 /= 2;
        y2 /= 2;

        for (int y = y1; y <= y2; ++y) {
            for (int b = 0; b < borderWidth / 2; ++b) {
                uvImage[y * width + (x1 + b)] = uColor;
                uvImage[y * width + (x2 - b)] = uColor;
            }
        }

        for (int x = x1; x <= x2; ++x) {
            for (int b = 0; b < borderWidth / 2; ++b) {
                uvImage[(y1 + b) * width + x] = uColor;
                uvImage[(y2 - b) * width + x] = uColor;
            }
        }

        // Draw V component rectangle border
        for (int y = y1; y <= y2; ++y) {
            for (int b = 0; b < borderWidth / 2; ++b) {
                uvImage[width * height + y * width + (x1 + b)] = vColor;
                uvImage[width * height + y * width + (x2 - b)] = vColor;
            }
        }

        for (int x = x1; x <= x2; ++x) {
            for (int b = 0; b < borderWidth / 2; ++b) {
                uvImage[width * height + (y1 + b) * width + x] = vColor;
                uvImage[width * height + (y2 - b) * width + x] = vColor;
            }
        }
    }



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

int main() {
    const int width = 2048;
    const int height = 1536;
    const int borderWidth = 8;
    const int x1 = 50;
    const int y1 = 50;
    const int x2 = 1000;
    const int y2 = 1200;

    // Read the YUV image from file
    std::ifstream inputFile("input.yuv", std::ios::binary);
    if (!inputFile) {
        std::cout << "Failed to open the YUV image file!" << std::endl;
        return -1;
    }

    // Allocate memory for the YUV image
    unsigned char* yuvImage = new unsigned char[width * height * 3 / 2];

    // Read YUV data
    inputFile.read(reinterpret_cast<char*>(yuvImage), width * height * 3 / 2);

    // Close the input file
    inputFile.close();

    // Draw a rectangle on the YUV image
    drawRectangle(yuvImage, width, height, x1, y1, x2, y2, borderWidth);

    // Save the modified YUV image to a file
    std::ofstream outputFile("output.yuv", std::ios::binary);
    if (!outputFile) {
        std::cout << "Failed to create the output YUV image file!" << std::endl;
        delete[] yuvImage;
        return -1;
    }

    // Write the modified YUV image to the output file
    outputFile.write(reinterpret_cast<const char*>(yuvImage), width * height * 3 / 2);

    // Close the output file
    outputFile.close();

    // Clean up memory
    delete[] yuvImage;

    return 0;
}
