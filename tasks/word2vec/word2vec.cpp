#include "word2vec.h"
#include <vector>
#include <limits>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<int64_t> diff = {0};
    int64_t max_value = std::numeric_limits<int64_t>::min();
    for (size_t i = 1; i < vectors.size(); ++i) {
        int64_t sum = 0;
        for (size_t j = 0; j < vectors[i].size(); ++j) {
            sum += vectors[0][j] * vectors[i][j];
        }
        diff.push_back(sum);
        if (sum > max_value) {
            max_value = sum;
        }
    }
    std::vector<std::string> ans = {};
    for (size_t i = 1; i < vectors.size(); ++i) {
        if (diff[i] == max_value) {
            ans.push_back(words[i]);
        }
    }
    return ans;
}
