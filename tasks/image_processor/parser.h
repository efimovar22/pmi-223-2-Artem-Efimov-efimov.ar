#pragma once

#include <vector>
#include <string>

struct ParsedFilter {
    std::string Word;
    std::vector<std::string> Par;
    void Clear();
    std::string GetWord() const;
    std::vector<std::string> GetPar() const;
};
std::vector<ParsedFilter> ParseArgs(int argc, char* argv[]);
