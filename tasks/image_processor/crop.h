#pragma once

#include "filter.h"
#include "image.h"

class Crop : public Filter {
public:
    Crop(size_t height, size_t width);
    Image Apply(const Image& image) const override;

private:
    size_t height_;
    size_t width_;
};
