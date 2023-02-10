#include "tests_checking.h"
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> d = {};
    for (size_t i = 0; i < student_actions.size(); ++i) {
        if (student_actions[i].side == Side::Top) {
            d.push_front(student_actions[i].name);
        } else {
            d.push_back(student_actions[i].name);
        }
    }
    std::vector<std::string> ans = {};
    for (size_t i = 0; i < queries.size(); ++i) {
        ans.push_back(d[queries[i] - 1]);
    }
    return ans;
}