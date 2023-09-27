#include <cassert>
#include <iostream>
#include <string>

#include "utf8.h"

int main(void) {
    std::string s1("落花流水a");
    // Count
    auto n1 = utf8::Count(s1);
    assert(n1 == 5);
    // Decode
    std::u32string p1(n1, 0);
    assert(utf8::Decode(s1, p1) == n1);
    assert(p1[0] == 33853);  // 落
    assert(p1[1] == 33457);  // 花
    assert(p1[2] == 27969);  // 流
    assert(p1[3] == 27700);  // 水
    assert(p1[4] == 97);     // a

    // Encode
    std::string s2(4 * n1, 0);
    auto k = utf8::Encode(p1, s2);
    assert(k > 0);
    s2.resize(k);
    assert(s1 == s2);
    return 0;
}
