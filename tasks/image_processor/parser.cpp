#include "parser.h"

void ParsedFilter::Clear() {
    Word.clear();
    Par.clear();
}

std::string ParsedFilter::GetWord() const {
    return Word;
}

std::vector<std::string> ParsedFilter::GetPar() const {
    return Par;
}

std::vector<ParsedFilter> ParseArgs(int argc, char* argv[]) {
    std::vector<ParsedFilter> ans;
    ParsedFilter now;
    for (size_t i = 0; i < static_cast<size_t>(argc); ++i) {
        std::string str(argv[i]);
        if (i > 2) {
            if (str.front() == '-') {
                if (!(now.GetWord().empty() && now.Par.empty())) {
                    ans.push_back(now);
                    now.Clear();
                }
                now.Word = str;
            } else {
                now.Par.push_back(str);
            }
        } else {
            now.Word = str;
            ans.push_back(now);
            now.Clear();
        }
    }
    if (!(now.Word.empty() && now.Par.empty())) {
        ans.push_back(now);
    }
    return ans;
}
