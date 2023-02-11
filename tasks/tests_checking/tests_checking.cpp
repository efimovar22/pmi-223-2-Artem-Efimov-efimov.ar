#include "tests_checking.h"
#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> d = {};
    for (const StudentAction& i : student_actions) {
        if (i.side == Side::Top) {
            d.push_front(i.name);
        } else {
            d.push_back(i.name);
        }
    }
    std::vector<std::string> ans = {};
    for (auto i : queries) {
        ans.push_back(d[i - 1]);
    }
    return ans;
}