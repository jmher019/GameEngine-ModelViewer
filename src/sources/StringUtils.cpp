#include <StringUtils.hpp>

vector<string> StringUtils::split(const string& str, const char& delim) {
    size_t begin = 0;

    vector<string> results;
    for (size_t i = 0; i < str.length(); i++) {
        const char currChar = str.at(i);

        if (currChar == delim) {
            if (i == begin) {
                results.push_back(string(""));
            }
            else {
                results.push_back(str.substr(begin, i - begin));
            }
            begin = i + 1;
        }
    }

    if (begin != str.length()) {
        results.push_back(str.substr(begin, str.length() - begin));
    }
    else if (results.empty()) {
        results.push_back(str);
    }

    return results;
}