#include "password.h"

#include <iostream>

constexpr int Cnst126 = 126;
constexpr int Cnst33 = 33;
constexpr int Cnst8 = 8;
constexpr int Cnst14 = 14;
constexpr int Cnst3 = 3;

bool ValidatePassword(const std::string& password) {
    int big_letters = 0;
    int small_letters = 0;
    int numbers = 0;
    int other = 0;
    if (password.size() < Cnst8 || password.size() > Cnst14) {
        return false;
    }
    for (size_t i = 0; i < password.size(); ++i) {
        if (int(password[i]) < Cnst33 || int(password[i]) > Cnst126) {
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
    if (big_letters + small_letters + numbers + other < Cnst3) {
        return false;
    }
    return true;
}
