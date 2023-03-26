#pragma once

#include "color.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

class Image {
public:
    Image() = default;
    Image(size_t height, size_t width);
    Image(const Image& other);
    explicit Image(const std::vector<std::vector<Color>>& other);
    ~Image() = default;
    size_t Height() const;
    size_t Width() const;
    const std::vector<std::vector<Color>>& GetColorsVector() const;
    std::vector<Color>& operator[](ssize_t i);
    std::vector<Color>& operator[](size_t i);
    const std::vector<Color>& operator[](size_t i) const;
    Color& GetColor(size_t x, size_t y);
    const Color& GetColor(size_t x, size_t y) const;
    void MakeColor(size_t x, size_t y, Color color);
    void Read(const char* path);
    void Export(const char* path) const;

private:
    size_t height_ = 0;
    size_t width_ = 0;
    std::vector<std::vector<Color>> colors_;
};