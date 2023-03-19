#pragma once

#include <iterator>

template <typename T1, typename T2>
class ZipIterator {
public:
    ZipIterator(T1 a, T2 b) {
        iterator1_ = a;
        iterator2_ = b;
    };
    bool operator!=(const ZipIterator& other) {
        return iterator1_ != other.iterator1_ && iterator2_ != other.iterator2_;
    }
    auto operator++() {
        return std::make_pair(++iterator1_, ++iterator2_);
    }
    auto operator*() {
        return std::pair{*iterator1_, *iterator2_};
    }

private:
    T1 iterator1_;
    T2 iterator2_;
};

template <typename T1, typename T2>
class ZipObject {
public:
    ZipObject(T1 beg1, T1 end1, T2 beg2, T2 end2) : beg1_(beg1), end1_(end1), beg2_(beg2), end2_(end2) {
    }

    auto begin() {
        return ZipIterator(beg1_, beg2_);
    }

    auto end() {
        return ZipIterator(end1_, end2_);
    }

private:
    T1 beg1_;
    T1 end1_;
    T2 beg2_;
    T2 end2_;
};

template <typename Obj1, typename Obj2>
auto Zip(const Obj1& obj1, const Obj2& obj2) {
    return ZipObject(std::begin(obj1), std::end(obj1), std::begin(obj2), std::end(obj2));
}