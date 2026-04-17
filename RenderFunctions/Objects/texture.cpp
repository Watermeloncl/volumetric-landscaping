#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "texture.h"
#include "color.h"
#include "..\..\DataCenter\Objects\point.h"

Texture::Texture(const char* textureName) {
    std::ifstream f(std::string("DataCenter\\DataFiles\\Textures\\") + textureName + ".bmp", std::ios::binary);
    if (!f.is_open()) {
        std::cout << "couldn't load texture " << textureName << std::endl;
        return;
    }

    unsigned char header[54];
    f.read((char*)header, 54);

    // Basic BMP validation: starts with 'BM'
    if (header[0] != 'B' || header[1] != 'M') {
        std::cout << "invalid bmp " << textureName << std::endl;
        return;
    }

    this->width  = *(int*)&header[18];
    this->height = *(int*)&header[22];

    int channels = 3; // 24-bit = 3 bytes (B, G, R)
    int rowSize = (this->width * channels + 3) & ~3; // Align to 4 bytes
    int size = rowSize * this->height;

    this->data = new unsigned char[size];
    f.read((char*)this->data, size);
    f.close();
}

Texture::~Texture() {
    delete[] this->data;
}

Color Texture::SampleTexture(Point* collisionPoint, Point* normal) {
    double u, v;

    // Pick the dominant axis of the normal to avoid stretching on sloped surfaces
    double absX = std::abs(normal->GetX());
    double absY = std::abs(normal->GetY());
    double absZ = std::abs(normal->GetZ());

    if (absX >= absY && absX >= absZ) {
        // Most "Side-facing" (YZ plane)
        u = collisionPoint->GetY();
        v = collisionPoint->GetZ();
    } else if (absY >= absX && absY >= absZ) {
        // Most "Top-facing" (XZ plane)
        u = collisionPoint->GetX();
        v = collisionPoint->GetZ();
    } else {
        // Most "Front-facing" (XY plane)
        u = collisionPoint->GetX();
        v = collisionPoint->GetY();
    }

    // Ensure U and V stay within [0, 1] range for the texture
    // Modulo 1.0 allows the texture to repeat if coordinates are outside 1x1
    u = u - std::floor(u);
    v = v - std::floor(v);

    int px = static_cast<int>(u * (this->width - 1));
    int py = static_cast<int>(v * (this->height - 1));

    // BMPs are stored bottom-to-top usually
    py = (this->height - 1) - py;

    int rowSize = (this->width * 3 + 3) & ~3;
    int index = (py * rowSize) + (px * 3);

    // Extract BGR and convert to 0.0 - 1.0 float
    double inv = 1 / 255.0;
    return Color(
        this->data[index + 2] * inv, // R
        this->data[index + 1] * inv, // G
        this->data[index]     * inv  // B
    );
}