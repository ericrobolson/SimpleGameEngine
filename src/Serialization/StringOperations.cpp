#include "StringOperations.h"
#include <string>


int StringOperations::ParseIntegers(std::string s){
    int num = 0;

    if (s.empty()){
        return num;
    }

    const int minusChar = 45; // ascii char code for -
    const int zeroCharValue = 48; // ascii char code for 0
    const int nineCharValue = zeroCharValue + 9; // ascii char code for 9

    std::string str;

    for (int i = 0; i < s.size(); i++){
        int c = (int)s[i];

        if (c >=  zeroCharValue && c <= nineCharValue){
            int numberToAdd = c - minusChar;

            str.push_back(s[i]);
        }
    }

    num = std::stoi(str);

    if ((int)s[0] == minusChar){
        num = (-1) * num;
    }

    return num;
}


std::string StringOperations::RemoveSubstring(std::string s, std::string subString){
    if (s.empty() || subString.empty()){
        return s;
    }

    size_t start_pos = s.find(subString);
    if (start_pos != std::string::npos){
        s.replace(start_pos, subString.length(), "");

        s = RemoveSubstring(s, subString);
    }

    return s;
}

std::string StringOperations::RemoveWhitespace(std::string s){
    s = RemoveSubstring(s, " ");
    s = RemoveSubstring(s, "\n");
    s = RemoveSubstring(s, "\r");
    s = RemoveSubstring(s, "\t");

    return s;
}
