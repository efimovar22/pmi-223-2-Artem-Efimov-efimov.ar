#pragma once

#include "filter.h"

class FilterSequence : public Filter {
public:
    void AddFilter(Filter* filer);
    Image Apply(const Image&) const override;

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};