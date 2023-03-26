#include "gaussian_blur.h"

GaussianBlur::GaussianBlur(double sigma) : sigma_(sigma) {
}
const double TWO = 2.0;
Image GaussianBlur::Apply(const Image &image) const {
    std::vector<std::vector<Color>> ans;
    double r = 0.0;
    double s = TWO * sigma_ * sigma_;
    double sum_r = 0.0;
    double sum_g = 0.0;
    double sum_b = 0.0;
    for (size_t x = 0; x < image.Height(); ++x) {
        std::vector<Color> now(image.Width());
        for (size_t y = 0; y < image.Width(); ++y) {
            r = static_cast<double>(std::sqrt(x * x + y * y));
            now[y] = {(exp(-(r * r) / s)) / (M_PI * s), (exp(-(r * r) / s)) / (M_PI * s),
                      (exp(-(r * r) / s)) / (M_PI * s)};
            sum_r += image[x][y].Red;
            sum_g += image[x][y].Red;
            sum_b += image[x][y].Red;
        }
        ans.push_back(now);
    }

    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            ans[i][j].Red = image[i][j].Red / sum_r;
            ans[i][j].Green = image[i][j].Green / sum_g;
            ans[i][j].Blue = image[i][j].Blue / sum_b;
        }
    }
    return Image(ans);
}
