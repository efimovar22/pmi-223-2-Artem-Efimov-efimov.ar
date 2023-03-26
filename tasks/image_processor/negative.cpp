#include "negative.h"

const int16_t BIT_BMP = 1;
Image Negative::Apply(const Image& image) const {
    std::vector<std::vector<Color>> ans;
    for (size_t i = 0; i < image.Height(); ++i) {
        std::vector<Color> vec(image.Width());
        for (size_t j = 0; j < image.Width(); ++j) {
            vec[j] = {static_cast<double>(BIT_BMP - image.GetColor(i, j).Red),
                      static_cast<double>(BIT_BMP - image.GetColor(i, j).Green),
                      static_cast<double>(BIT_BMP - image.GetColor(i, j).Blue)};
        }
        ans.push_back(vec);
    }
    return Image(ans);
}