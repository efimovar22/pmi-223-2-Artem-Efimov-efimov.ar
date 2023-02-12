#include "scorer.h"
#include <algorithm>

bool TimeComparator(const Event* event_1, const Event* event_2) {
    return event_1->time < event_2->time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable ans = {};
    std::map<std::string, std::map<std::string, std::pair<int, int>>> check_tasks;
    std::vector<const Event*> sorted_events;
    for (auto& i : events) {
        sorted_events.push_back(&i);
    }
    std::sort(sorted_events.begin(), sorted_events.end(), TimeComparator);
    for (auto& i : sorted_events) {
        if (i->time > score_time) {
            break;
        }
        if (not check_tasks.contains(i->student_name)) {
            check_tasks[i->student_name][i->task_name].first = 0;
            check_tasks[i->student_name][i->task_name].second = 0;
        }
        if (not check_tasks[i->student_name].contains(i->task_name)) {
            check_tasks[i->student_name][i->task_name].first = 0;
            check_tasks[i->student_name][i->task_name].second = 0;
        }
        if (i->event_type == EventType::CheckSuccess) {
            check_tasks[i->student_name][i->task_name].first = 1;
        } else if (i->event_type == EventType::MergeRequestOpen) {
            check_tasks[i->student_name][i->task_name].second = 1;
        } else if (i->event_type == EventType::MergeRequestClosed) {
            check_tasks[i->student_name][i->task_name].second = 0;
        } else if (i->event_type == EventType::CheckFailed) {
            check_tasks[i->student_name][i->task_name].second = 0;
        }
    }
    for (const auto& [i, j] : check_tasks) {
        for (const auto& [a, b] : j) {
            if (b.first == 1 && b.second == 0) {
                ans[i].insert(a);
            }
        }
    }
    return ans;
}
