#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H
#include <string>

class StringOperations
{
    public:
        static int ParseIntegers(std::string s);
        static std::string RemoveSubstring(std::string s, std::string subString);
        static std::string RemoveWhitespace(std::string s);
};

#endif // STRINGOPERATIONS_H
