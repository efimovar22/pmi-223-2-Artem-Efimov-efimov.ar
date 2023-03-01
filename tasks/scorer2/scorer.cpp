#include "scorer.h"
void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    check_tasks[student_name][task_name].first = false;
}
void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    check_tasks[student_name][task_name].first = true;
}
void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    check_tasks[student_name][task_name].second = true;
}
void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    check_tasks[student_name][task_name].second = false;
}
void Scorer::Reset() {
    check_tasks.clear();
}
ScoreTable Scorer::GetScoreTable() const{
    std::map<StudentName, std::set<TaskName>> ans;
    for (const auto& [i, j] : check_tasks) {
       for (const auto& [a, b] : j) {
           if (b.first && not b.second) {
               ans[i].insert(a);
           }
       }
    }
    return ans;
}
