#include "edge_detection.h"
#include "grayscale.h"

const std::vector<std::vector<int16_t>> MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
Image EdgeDetection::Apply(const Image& image) const {
    std::vector<std::vector<Color>> ans;
    for (size_t i = 0; i < image.Height(); ++i) {
        std::vector<Color> vec(image.Width());
        for (size_t j = 0; j < image.Width(); ++j) {
            vec[j].Red = -(image.GetColorsVector()[std::max(i, static_cast<size_t>(1)) - 1][j].Red +
                           image.GetColorsVector()[std::min(i + 1, image.Height() - 1)][j].Red +
                           image.GetColorsVector()[i][std::max(j, static_cast<size_t>(1)) - 1].Red +
                           image.GetColorsVector()[i][std::min(j + 1, image.Width() - 1)].Red) +
                         4 * image.GetColorsVector()[i][j].Red;
            vec[j].Green = -(image.GetColorsVector()[std::max(i, static_cast<size_t>(1)) - 1][j].Green +
                             image.GetColorsVector()[std::min(i + 1, image.Height() - 1)][j].Green +
                             image.GetColorsVector()[i][std::max(j, static_cast<size_t>(1)) - 1].Green +
                             image.GetColorsVector()[i][std::min(j + 1, image.Width() - 1)].Green) +
                           4 * image.GetColorsVector()[i][j].Green;
            vec[j].Blue = -(image.GetColorsVector()[std::max(i, static_cast<size_t>(1)) - 1][j].Blue +
                            image.GetColorsVector()[std::min(i + 1, image.Height() - 1)][j].Blue +
                            image.GetColorsVector()[i][std::max(j, static_cast<size_t>(1)) - 1].Blue +
                            image.GetColorsVector()[i][std::min(j + 1, image.Width() - 1)].Blue) +
                          4 * image.GetColorsVector()[i][j].Blue;
        }
        ans.push_back(vec);
    }
    for (auto& i : ans) {
        for (auto& j : i) {
            if (j.Red > threshold_) {
                j.Red = 1;
            } else {
                j.Red = 0;
            }
            if (j.Green > threshold_) {
                j.Green = 1;
            } else {
                j.Green = 0;
            }
            if (j.Blue > threshold_) {
                j.Blue = 1;
            } else {
                j.Blue = 0;
            }
        }
    }
    return Image(ans);
}
EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {
}
