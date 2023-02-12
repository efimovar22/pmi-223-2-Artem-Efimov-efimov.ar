#include "scorer.h"
#include <algorithm>

bool TimeComparator(const Event* event_1, const Event* event_2) {
    return event_1->time > event_2->time;
}

bool ExistsName(const std::string& name) {
    std::map<std::string, std::map<std::string, int>> check_tasks;
    return check_tasks.find(name) != check_tasks.end();
}

bool ExistsProblem(const std::string& s, const std::string& name) {
    std::map<std::string, std::map<std::string, int>> check_tasks;
    return check_tasks[s].find(name) != check_tasks[s].end();
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable ans = {};
    std::map<std::string, std::map<std::string, int>> check_tasks;
    std::vector<const Event*> sorted_events;
    for (auto& i : events) {
        sorted_events.push_back(&i);
    }
    std::sort(sorted_events.begin(), sorted_events.end(), TimeComparator);
    for (auto& i : sorted_events) {
        if (i->time > score_time) {
            break;
        }
        if (not ExistsName(i->student_name)) {
            check_tasks[i->student_name][i->task_name] = 0;
        } else if (not ExistsProblem(i->student_name, i->task_name)) {
            check_tasks[i->student_name][i->task_name] = 0;
        }
        if (i->event_type == EventType::CheckSuccess && check_tasks[i->student_name][i->task_name] != 3) {
            check_tasks[i->student_name][i->task_name] = 1;
        } else if (i->event_type == EventType::MergeRequestOpen) {
            check_tasks[i->student_name][i->task_name] = 3;
        } else if (i->event_type == EventType::MergeRequestClosed) {
            check_tasks[i->student_name][i->task_name] = 0;
        }
    }
    for (const auto& [i, j] : check_tasks) {
        for (const auto& [a, b] : j) {
            if (b == 1) {
                ans[i].insert(a);
            }
        }
    }
    return ans;
}
