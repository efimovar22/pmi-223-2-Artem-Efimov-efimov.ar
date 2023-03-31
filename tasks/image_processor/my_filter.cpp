#include "my_filter.h"

Image MyFilter::Apply(const Image& image) const {
    const double red_param = 0.2;
    const double green_param = 0.5;
    const double blue_param = 0.3;
    std::vector<std::vector<Color>> ans;
    for (size_t i = 0; i < image.Height(); ++i) {
        std::vector<Color> now(image.Width());
        for (size_t j = 0; j < image.Width(); ++j) {
            double color = image.GetColor(i, j).Red * red_param + image.GetColor(i, j).Green * green_param +
                           image.GetColor(i, j).Blue * blue_param;
            now[j] = {color, color, color};
        }
        ans.push_back(now);
    }
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            ans[i][j] = ans[j][i];
        }
    }
    return Image(ans);
}