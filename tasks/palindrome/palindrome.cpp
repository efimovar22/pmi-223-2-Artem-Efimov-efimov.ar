#include "palindrome.h"

#include <string>

bool IsPalindrome(const std::string& str) {
    int left = 0;
    int right = str.size() - 1;
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
