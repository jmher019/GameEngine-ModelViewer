#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <vector>

using namespace std;

class StringUtils {
public:
    static vector<string> split(const string& str, const char& delim);
};

#endif // !STRING_UTILS_HPP
