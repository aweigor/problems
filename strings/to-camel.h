#include <vector>
#include <string>
#include <regex>

std::string to_camel_case(std::string text) {
    std::regex re("[_\-][A-Za-z]");
    std::smatch match;
    std::string result;
    for (std::smatch sm; std::regex_search(text, sm, re); text = sm.suffix()) {
        result += sm.prefix();
        result += std::toupper(std::string(sm[0])[1]);
    }
    result += text;
    return result;
}

std::string to_camel_case_bp(std::string s)
{
    for(int i{0}; i < s.size(); ++i)
        if(s[i] == '-' || s[i] == '_')
            s.erase(i, 1), s[i] = toupper(s[i]);
    return s;
}