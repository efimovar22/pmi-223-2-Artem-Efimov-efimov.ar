#pragma once

#include <initializer_list>
#include <map>
#include <iostream>
#include <vector>
#include <iterator>

class Poly {
public:
    void ZeroCoef();
    Poly() = default;
    Poly(std::initializer_list<std::pair<int64_t, int64_t>> poly);
    Poly(std::initializer_list<int64_t> poly);
    Poly(const Poly& other) = default;
    Poly operator+=(const Poly& other);
    Poly operator-=(const Poly& other);
    Poly operator*=(const Poly& other);
    Poly operator+(const Poly& other);
    Poly operator-(const Poly& other);
    Poly operator*(const Poly& other);
    Poly operator-() const;
    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;
    Poly operator=(const Poly& other);
    int64_t operator()(int64_t x) const;

private:
    friend std::ostream& operator<<(std::ostream& out, const Poly&);
    std::map<int64_t, int64_t> coeffs_;
};