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

    return 0;
}
