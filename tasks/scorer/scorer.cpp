#include "scorer.h"
#include <algorithm>

bool TimeComparator(const Event* event_1, const Event* event_2) {
    return event_1->time < event_2->time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable ans = {};
    std::map<std::string, std::map<std::string, std::pair<bool, bool>>> check_tasks;
    std::vector<const Event*> sorted_events;
    for (auto& i : events) {
        sorted_events.push_back(&i);
    }
    std::sort(sorted_events.begin(), sorted_events.end(), TimeComparator);
    for (auto& i : sorted_events) {
        if (i->time > score_time) {
            break;
        }
        if (i->event_type == EventType::CheckSuccess) {
            check_tasks[i->student_name][i->task_name].first = true;
        } else if (i->event_type == EventType::MergeRequestOpen) {
            check_tasks[i->student_name][i->task_name].second = true;
        } else if (i->event_type == EventType::MergeRequestClosed) {
            check_tasks[i->student_name][i->task_name].second = false;
        } else if (i->event_type == EventType::CheckFailed) {
            check_tasks[i->student_name][i->task_name].second = false;
        }
    }
    for (const auto& [i, j] : check_tasks) {
        for (const auto& [a, b] : j) {
            if (b.first && not b.second) {
                ans[i].insert(a);
            }
        }
    }
    return ans;
}
