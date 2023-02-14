#include "admission.h"

bool PointsComparator(const Applicant* applicant_1, const Applicant* applicant_2) {
    return std::tie(applicant_1->points, applicant_2->student.birth_date.year, applicant_2->student.birth_date.month,
                    applicant_2->student.birth_date.day, applicant_1->student.name) >
           std::tie(applicant_2->points, applicant_1->student.birth_date.year, applicant_1->student.birth_date.month,
                    applicant_1->student.birth_date.day, applicant_2->student.name);
}

bool NameComparator(const Student* student_1, const Student* student_2) {
    return std::tie(student_1->name, student_1->birth_date.year, student_1->birth_date.month,
                    student_1->birth_date.day) < std::tie(student_2->name, student_2->birth_date.year,
                                                          student_2->birth_date.month, student_2->birth_date.day);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    AdmissionTable ans;
    std::vector<const Applicant*> sorted_applicants;
    for (const auto& i : applicants) {
        sorted_applicants.push_back(&i);
    }
    std::sort(sorted_applicants.begin(), sorted_applicants.end(), PointsComparator);
    std::unordered_map<std::string, size_t> uni;
    for (auto& i : universities) {
        uni[i.name] = i.max_students;
    }
    for (const auto& i : sorted_applicants) {
        for (const auto& j : i->wish_list) {
            if (uni[j] > 0) {
                ans[j].push_back(&i->student);
                uni[j] -= 1;
                break;
            }
        }
    }
    for (auto& i : ans) {
        std::sort(i.second.begin(), i.second.end(), NameComparator);
    }
    return ans;
}
