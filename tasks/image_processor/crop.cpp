#include "crop.h"

Crop::Crop(size_t height, size_t width) : height_(height), width_(width) {
}

Image Crop::Apply(const Image &image) const {
    Image ans(std::min(image.Height(), height_), std::min(image.Width(), width_));  // cut
    for (size_t i = 0; i < std::min(image.Height(), height_); ++i) {
        for (size_t j = 0; j < std::min(image.Width(), width_); ++j) {
            ans.MakeColor(i, j, image.GetColorsVector()[i + image.Height() - std::min(image.Height(), height_)][j]);
        }
    }
    return ans;
}