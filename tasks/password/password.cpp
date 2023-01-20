#include "password.h"

#include <iostream>

bool ValidatePassword(const std::string& password) {
    int big_letters = 0;
    int small_letters = 0;
    int numbers = 0;
    int other = 0;
    if (password.size() < 8 || password.size() > 14) {
        return false;
    }
    for (size_t i = 0; i < password.size(); ++i) {
        if (int(password[i]) < 33 || int(password[i]) > 126) {
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
        if (std::islower(static_cast<unsigned char>(password[i]))) {
            numbers = 1;
            continue;
        }
        other = 1;
    }
    if (big_letters + small_letters + numbers + other < 3) {
        return false;
    }
    return true;
}
