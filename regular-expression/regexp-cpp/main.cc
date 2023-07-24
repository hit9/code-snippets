#include <iostream>

#include "regexp.hpp"

int main(void) {
    auto dfa = regexp::Compile("a(a|b)*c(d|e)(x|y|z)*");
    std::cout << dfa->Match("aabbace") << std::endl;          // 1
    std::cout << dfa->Match("aabbbbbbace") << std::endl;      // 1
    std::cout << dfa->Match("aabbbbbbacd") << std::endl;      // 1
    std::cout << dfa->Match("aabbbbbbad") << std::endl;       // 0
    std::cout << dfa->Match("aabbbbbbaf") << std::endl;       // 0
    std::cout << dfa->Match("aabbbbbbacdxxx") << std::endl;   // 1
    std::cout << dfa->Match("aabbbbbbacdxzy") << std::endl;   // 1
    std::cout << dfa->Match("aabbbbbbacdxzy1") << std::endl;  // 0

    auto dfa1 = regexp::Compile("aa*(b|c)*abc");
    std::cout << dfa1->Match("aababc") << std::endl;
    std::cout << dfa1->Match("acabc") << std::endl;
    std::cout << dfa1->Match("aabc") << std::endl;
    std::cout << dfa1->Match("aabaabc") << std::endl;
    std::cout << dfa1->Match("abbabc") << std::endl;
    std::cout << dfa1->Match("aacx") << std::endl;

    auto dfa2 = regexp::Compile("abc(e|f)g*(ab)*ab");
    std::cout << dfa2->Match("abcegabab") << std::endl;
    std::cout << dfa2->Match("abcegababab") << std::endl;
    std::cout << dfa2->Match("abcfgababab") << std::endl;
    std::cout << dfa2->Match("abckgababab") << std::endl;

    auto dfa3 = regexp::Compile("abab(ab)*cd(e|f)*abc");
    std::cout << dfa3->Match("abababcdeabc") << std::endl;        // 1
    std::cout << dfa3->Match("abababcdfabc") << std::endl;        // 1
    std::cout << dfa3->Match("ababababababcdfabc") << std::endl;  // 1
    std::cout << dfa3->Match("abababababacdfabc") << std::endl;   // 0
    std::cout << dfa3->Match("abababababacdeabc") << std::endl;   // 0

    return 0;
}
