#pragma once

#include "filter.h"

class EdgeDetection : public Filter {
public:
    Image Apply(const Image& image) const override;
    EdgeDetection(int threshold);

private:
    double threshold_;
};