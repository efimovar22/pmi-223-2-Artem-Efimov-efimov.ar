#include "unixpath.h"
#include <vector>
#include <iostream>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::vector<std::string> now_path{""};
    for (const auto& i : current_working_dir) {
        if (i != '/') {
            now_path[now_path.size() - 1] += i;
        } else {
            now_path.push_back("");
        }
    }
    std::vector<std::string> vector_path{""};
    for (const auto& i : path) {
        if (i != '/') {
            vector_path[vector_path.size() - 1] += i;
        } else {
            vector_path.push_back("");
        }
    }
    for (const auto &i : vector_path) {
        if (i == "..") {
            if (!now_path.empty()) {
                now_path.pop_back();
            }
        } else if (!i.empty() && i != "." && i != "/" && i != "//" && i != " ") {
            now_path.push_back(i);
        }
    }
    std::string ans;
    for (const auto& i : now_path) {
        if (!i.empty() && i != "." && i != "/" && i != "//" && i != " ") {
            ans += "/";
            ans += i;
        }
    }
    if (!ans.empty()) {
        return ans;
    } else {
        ans = "/";
        return ans;
    }
}
