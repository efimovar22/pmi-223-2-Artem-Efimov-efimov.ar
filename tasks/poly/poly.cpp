#include "poly.h"
void Poly::ZeroCoef() {
    for (auto iter = coeffs_.begin(); iter != coeffs_.end();) {
        if (iter->second == 0) {
            iter = coeffs_.erase(iter);
        } else {
            ++iter;
        }
    }
};

Poly::Poly(std::initializer_list<std::pair<int64_t, int64_t>> poly) : coeffs_(poly.begin(), poly.end()) {
    ZeroCoef();
}

Poly::Poly(std::initializer_list<int64_t> poly) {
    auto iter = poly.begin();
    int64_t i = 0;
    while (iter != poly.end()) {
        coeffs_[i] = *iter;
        ++iter;
        ++i;
    }
    ZeroCoef();
}

Poly Poly::operator+=(const Poly& other) {
    for (auto [x, y] : other.coeffs_) {
        if (coeffs_.count(x) == 0) {
            coeffs_[x] = y;
        } else {
            coeffs_[x] += y;
        }
    }
    ZeroCoef();
    return *this;
}

Poly Poly::operator-=(const Poly& other) {
    for (auto [x, y] : other.coeffs_) {
        if (coeffs_.count(x) == 0) {
            coeffs_[x] = y;
        } else {
            coeffs_[x] -= y;
        }
    }
    ZeroCoef();
    return *this;
}

Poly Poly::operator+(const Poly& other) {
    Poly ans = *this;
    ans += other;
    ans.ZeroCoef();
    return ans;
}

Poly Poly::operator-(const Poly& other) {
    Poly ans = *this;
    ans += -other;
    ans.ZeroCoef();
    return ans;
}

Poly Poly::operator*(const Poly& other) {
    Poly ans = Poly();
    for (auto [x, y] : coeffs_) {
        for (auto [x1, y1] : other.coeffs_) {
            if (ans.coeffs_.count(x + x1) == 0) {
                ans.coeffs_[x + x1] = y * y1;
            } else {
                ans.coeffs_[x + x1] += y * y1;
            }
        }
    }
    ans.ZeroCoef();
    return ans;
}

Poly Poly::operator*=(const Poly& other) {
    *this = *this + other;
    return *this;
}

Poly Poly::operator-() const {
    Poly ans = Poly(*this);
    for (auto [x, y] : coeffs_) {
        ans.coeffs_[x] = -y;
    }
    ans.ZeroCoef();
    return ans;
}

bool Poly::operator==(const Poly& other) const {
    return coeffs_ == other.coeffs_;
}

bool Poly::operator!=(const Poly& other) const {
    return !(*this == other);
}

Poly Poly::operator=(const Poly& other) {
    coeffs_ = other.coeffs_;
    ZeroCoef();
    return *this;
}

int64_t Poly::operator()(int64_t x) const {
    int64_t ans = 0;
    for (const auto& [pow, cef] : coeffs_) {
        int64_t t = cef;
        for (int64_t i = 0; i < pow; ++i) {
            t *= x;
        }
        ans += t;
    }
    return ans;
}

std::ostream& operator<<(std::ostream& out, const Poly& data) {
    out << "y =";
    if (data.coeffs_.empty()) {
        out << " 0";
        return out;
    }
    bool b = true;
    auto iter = data.coeffs_.end();
    while (true) {
        if (iter->second != 0) {
            if (b) {
                b = false;
                out << " " << iter->second;
                if (iter->first != 0) {
                    out << "x^" << iter->first;
                }
            } else {
                if (iter->second > 0) {
                    out << " + " << iter->second;
                    if (iter->first != 0) {
                        out << "x^" << iter->first;
                    }
                } else {
                    out << " - " << -iter->second;
                    if (iter->first != 0) {
                        out << "x^" << iter->first;
                    }
                }
            }
        }
        if (iter == data.coeffs_.begin()) {
            break;
        }
        --iter;
    }

    return out;
}