#include "Utils.h"

#include <sstream>

using namespace std;
string& itoa(string& answer, int i) {
    stringstream ss;
    ss << i;
    answer = ss.str();
    return answer;
}

bool isAlpha(char c) {
	return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

bool isNum(char c) {
	return (c >= 48 && c <= 57);
}

bool isAlphaNum(char c) {
	return isAlpha(c) || isNum(c);
}

std::vector<std::string> split(std::string string, char delimiter) {
    std::vector<std::string> v;
    int start = 0;
    
    for (int i = 0; i < string.length(); i++) {
        if (string.at(i) == delimiter) {
            int pos = (int)string.find_first_of(delimiter, start);
            v.push_back(string.substr(start, pos-start));
            start = i+1;
        }
    }
    return v;
}