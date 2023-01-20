#include "palindrome.h"

#include <string>

bool IsPalindrome(const std::string& str) {
    int64_t left = 0;
    int64_t right = str.size() - 1;
    while (left < right) {
        while (left < str.size() && str[left] == ' ') {
            ++left;
        }
        while (right > 0 && str[right] == ' ') {
            --right;
        }
        if (left < right && str[left] != str[right]) {
            return false;
        } else {
            ++left;
            --right;
        }
    }
    return true;
}
