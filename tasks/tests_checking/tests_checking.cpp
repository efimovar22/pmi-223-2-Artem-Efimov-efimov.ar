#include "tests_checking.h"
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> d = {};
    for (StudentAction i : student_actions) {
        if (i.side == Side::Top) {
            d.push_front(i.name);
        } else {
            d.push_back(i.name);
        }
    }
    std::vector<std::string> ans = {};
    for (size_t i = 0; i < queries.size(); ++i) {
        ans.push_back(d[queries[i] - 1]);
    }
    return ans;
}