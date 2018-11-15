#include "catch.hpp"
#include "StringOperations.h"
#include <string>

SCENARIO("StringOperations::ParseIntegers"){
    REQUIRE(0 == StringOperations::ParseIntegers(""));
    REQUIRE(0 == StringOperations::ParseIntegers("000"));
    REQUIRE(1 == StringOperations::ParseIntegers("001"));
    REQUIRE(1 == StringOperations::ParseIntegers("00abas1"));
    REQUIRE(10 == StringOperations::ParseIntegers("00abas10"));
    REQUIRE(-10 == StringOperations::ParseIntegers("-00abas10"));
    REQUIRE(-910 == StringOperations::ParseIntegers("-00aba9s10"));
    REQUIRE(91110 == StringOperations::ParseIntegers(" 9   111asdf    0  "));
}

SCENARIO("StringOperations::RemoveSubstring "){
    REQUIRE("" == StringOperations::RemoveSubstring("",""));
    REQUIRE("a" == StringOperations::RemoveSubstring("a",""));
    REQUIRE("aaa" == StringOperations::RemoveSubstring("ababa","b"));
    REQUIRE("aaa" == StringOperations::RemoveSubstring("aaa","b"));
    REQUIRE("aaa" == StringOperations::RemoveSubstring("axtbaxtbaxtb","xtb"));
    REQUIRE("John " == StringOperations::RemoveSubstring("John Doe","Doe"));
}

SCENARIO("StringOperations::RemoveWhitespace "){
    REQUIRE("" == StringOperations::RemoveWhitespace(""));
    REQUIRE("a" == StringOperations::RemoveWhitespace(" a  "));
    REQUIRE("a" == StringOperations::RemoveWhitespace("\ta"));
    REQUIRE("a" == StringOperations::RemoveWhitespace("\ra"));
    REQUIRE("aa" == StringOperations::RemoveWhitespace("a\ra"));
    REQUIRE("a" == StringOperations::RemoveWhitespace("\na"));
    REQUIRE("a" == StringOperations::RemoveWhitespace("\na\n"));
    REQUIRE("" == StringOperations::RemoveWhitespace("\n\t\r "));
}
