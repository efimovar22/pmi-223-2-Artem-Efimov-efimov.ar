#pragma once

#include "filter.h"

class EdgeDetection : public Filter {
public:
    Image Apply(const Image& image) const override;
    explicit EdgeDetection(double threshold);

private:
    double threshold_;
};