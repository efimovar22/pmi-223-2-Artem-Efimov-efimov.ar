#pragma once

#include "image.h"
#include <memory>
#include <cstdlib>
#include <cmath>

class Filter {
public:
    virtual ~Filter() = default;
    virtual Image Apply(const Image& image) const = 0;
};