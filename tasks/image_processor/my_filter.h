#pragma once

#include "filter.h"

class MyFilter : public Filter {
public:
    Image Apply(const Image& image) const override;
};