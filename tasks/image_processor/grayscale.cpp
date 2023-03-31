#include "grayscale.h"

const double RED_PARAM = 0.299;
const double GREEN_PARAM = 0.587;
const double BLUE_PARAM = 0.114;
Image Grayscale::Apply(const Image &image) const {
    std::vector<std::vector<Color>> ans;
    for (size_t i = 0; i < image.Height(); ++i) {
        std::vector<Color> now(image.Width());
        for (size_t j = 0; j < image.Width(); ++j) {
            double color = image.GetColor(i, j).Red * RED_PARAM + image.GetColor(i, j).Green * GREEN_PARAM +
                           image.GetColor(i, j).Blue * BLUE_PARAM;
            now[j] = {color, color, color};
        }
        ans.push_back(now);
    }
    return Image{ans};
}