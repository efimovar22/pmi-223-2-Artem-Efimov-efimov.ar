#include "sharpening.h"

const std::vector<std::vector<int16_t>> MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
Image Sharpening::Apply(const Image &image) const {
    std::vector<std::vector<Color>> ans;
    for (size_t i = 0; i < image.Height(); ++i) {
        std::vector<Color> vec(image.Width());
        for (size_t j = 0; j < image.Width(); ++j) {
            vec[j].Red = -(image.GetColorsVector()[std::max(i, static_cast<size_t>(1)) - 1][j].Red +
                       image.GetColorsVector()[std::min(i + 1, image.Height())][j].Red +
                       image.GetColorsVector()[i][std::max(j, static_cast<size_t>(1)) - 1].Red +
                       image.GetColorsVector()[i][std::min(j + 1, image.Width())].Red) +
                     5 * image.GetColorsVector()[i][j].Red;
            vec[j].Green = -(image.GetColorsVector()[std::max(i, static_cast<size_t>(1)) - 1][j].Green +
                       image.GetColorsVector()[std::min(i + 1, image.Height())][j].Green +
                       image.GetColorsVector()[i][std::max(j, static_cast<size_t>(1)) - 1].Green +
                       image.GetColorsVector()[i][std::min(j + 1, image.Width())].Green) +
                     5 * image.GetColorsVector()[i][j].Green;
            vec[j].Blue = -(image.GetColorsVector()[std::max(i, static_cast<size_t>(1)) - 1][j].Blue +
                       image.GetColorsVector()[std::min(i + 1, image.Height())][j].Blue +
                       image.GetColorsVector()[i][std::max(j, static_cast<size_t>(1)) - 1].Blue +
                       image.GetColorsVector()[i][std::min(j + 1, image.Width())].Blue) +
                     5 * image.GetColorsVector()[i][j].Green;
        }
        ans.push_back(vec);
    }
    return ans;
}