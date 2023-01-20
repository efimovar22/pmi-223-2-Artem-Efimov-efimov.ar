#include "password.h"

#include <iostream>

constexpr int Cnst_126 = 126;
constexpr int Cnst_33 = 33;
constexpr int Cnst_8 = 8;
constexpr int Cnst_14 = 14;
constexpr int Cnst_3 = 3;

bool ValidatePassword(const std::string& password) {
    int big_letters = 0;
    int small_letters = 0;
    int numbers = 0;
    int other = 0;
    if (password.size() < Cnst_8 || password.size() > Cnst_14) {
        return false;
    }
    for (size_t i = 0; i < password.size(); ++i) {
        if (int(password[i]) < Cnst_33 || int(password[i]) > Cnst_126) {
            return false;
        }
        if (std::isupper(static_cast<unsigned char>(password[i]))) {
            big_letters = 1;
            continue;
        }
        if (std::islower(static_cast<unsigned char>(password[i]))) {
            small_letters = 1;
            continue;
        }
        if (std::isdigit(static_cast<unsigned char>(password[i]))) {
            numbers = 1;
            continue;
        }
        other = 1;
    }
    if (big_letters + small_letters + numbers + other < Cnst_3) {
        return false;
    }
    return true;
}
