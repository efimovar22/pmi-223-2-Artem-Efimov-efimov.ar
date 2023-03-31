#include "filter_sequence.h"

Image FilterSequence::Apply(const Image& image) const {
    Image result = image;
    for (const auto& filter : filters_) {
        result = filter->Apply(result);
    }
    return result;
}

void FilterSequence::AddFilter(Filter* filter) {
    filters_.emplace_back(filter);
}