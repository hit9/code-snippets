// c++ main.cc -std=c++11
#include <assert.h>

#include <iostream>

#include "regexp.hpp"

int main(void) {
    auto dfa = regexp::Compile("a(a|b)*c(d|e)(x|y|z)*");
    assert(dfa->Match("aabbace"));
    assert(dfa->Match("aabbbbbbace"));
    assert(dfa->Match("aabbbbbbacd"));
    assert(!dfa->Match("aabbbbbbad"));
    assert(!dfa->Match("aabbbbbbaf"));
    assert(dfa->Match("aabbbbbbacdxxx"));
    assert(dfa->Match("aabbbbbbacdxzy"));
    assert(!dfa->Match("aabbbbbbacdxzy1"));

    auto dfa1 = regexp::Compile("aa*(b|c)*abc");
    assert(dfa1->Match("aababc"));
    assert(dfa1->Match("acabc"));
    assert(dfa1->Match("aabc"));
    assert(!dfa1->Match("aabaabc"));
    assert(dfa1->Match("abbabc"));
    assert(!dfa1->Match("aacx"));

    auto dfa2 = regexp::Compile("abc(e|f)g*(ab)*ab");
    assert(dfa2->Match("abcegabab"));
    assert(dfa2->Match("abcegababab"));
    assert(dfa2->Match("abcfgababab"));
    assert(!dfa2->Match("abckgababab"));

    auto dfa3 = regexp::Compile("abab(ab)*cd(e|f)*abc");
    assert(dfa3->Match("abababcdeabc"));
    assert(dfa3->Match("abababcdfabc"));
    assert(dfa3->Match("ababababababcdfabc"));
    assert(!dfa3->Match("abababababacdfabc"));
    assert(!dfa3->Match("abababababacdeabc"));

    auto dfa4 = regexp::Compile("a+b*(c|d)?x+");
    assert(dfa4->Match("abcx"));
    assert(dfa4->Match("abx"));
    assert(!dfa4->Match("ab"));
    assert(dfa4->Match("aaabbdxxx"));

    auto dfa5 = regexp::Compile("[a-zA-Z][0-9a-zA-Z]*");
    assert(dfa5->Match("abcd12345"));
    assert(dfa5->Match("name123"));
    assert(dfa5->Match("name1abac23"));
    assert(!dfa5->Match("0"));
    assert(!dfa5->Match("0abcd123"));
    assert(!dfa5->Match("02384"));
    assert(!dfa5->Match("a02384!"));

    auto dfa6 = regexp::Compile("[a-z]([0-9]+|[A-Z])?");
    assert(dfa6->Match("b"));
    assert(dfa6->Match("a78"));
    assert(dfa6->Match("aZ"));
    assert(!dfa6->Match("aa"));
    assert(!dfa6->Match("a09a"));

    auto dfa7 =
        regexp::Compile("((\\+|\\-)[0-9])?[0-9]*(([0-9].)|(.[0-9]))?[0-9]*");
    assert(dfa7->Match("+31.25"));
    assert(dfa7->Match("-31.25"));
    assert(!dfa7->Match("-.25"));
    assert(!dfa7->Match("-"));
    assert(dfa7->Match(".123"));
    assert(dfa7->Match("122."));
    assert(!dfa7->Match("1.1.1"));
    return 0;
}
