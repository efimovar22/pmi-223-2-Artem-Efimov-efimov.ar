#include "password.h"

#include <iostream>

const char MAX_POS_VAL = '~';
const char MIN_POS_VAL = '!';
const char MIN_NUM_SYMB = 8;
const char MAX_NUM_SYMB = 14;
const char DIFFERENT_TYPES = 3;

bool ValidatePassword(const std::string& password) {
    bool has_big_letters = 0;
    bool has_small_letters = 0;
    bool has_numbers = 0;
    bool has_other = 0;
    if (password.size() < MIN_NUM_SYMB || password.size() > MAX_NUM_SYMB) {
        return false;
    }
    for (size_t i = 0; i < password.size(); ++i) {
        if (password[i] < MIN_POS_VAL || password[i] > MAX_POS_VAL) {
            return false;
        }
        if (std::isupper(password[i])) {
            has_big_letters = 1;
            continue;
        }
        if (std::islower(password[i])) {
            has_small_letters = 1;
            continue;
        }
        if (std::isdigit(password[i])) {
            has_numbers = 1;
            continue;
        }
        has_other = 1;
    }
    if (has_big_letters + has_small_letters + has_numbers + has_other < DIFFERENT_TYPES) {
        return false;
    }
    return true;
}
