#include <cassert>
#include <string>

#include "utf8.h"

void test1() {
    std::string s("落花流水a");
    // Count
    auto n = utf8::Count(s);
    assert(n == 5);
    // Decode
    std::u32string p(n, 0);
    assert(utf8::Decode(s, p) == n);
    assert(p[0] == 33853);  // 落
    assert(p[1] == 33457);  // 花
    assert(p[2] == 27969);  // 流
    assert(p[3] == 27700);  // 水
    assert(p[4] == 97);     // a

    // Encode
    std::string s1(4 * n, 0);
    auto k = utf8::Encode(p, s1);
    assert(k > 0);
    s1.resize(k);
    assert(s == s1);
}

void test2() {
    std::string s("$123¢€🙂");
    // Count
    auto n = utf8::Count(s);
    assert(n == 7);
    // Decode
    std::u32string p(n, 0);
    assert(utf8::Decode(s, p) == n);
    assert(p[0] == 36);
    assert(p[1] == 49);
    assert(p[2] == 50);
    assert(p[3] == 51);
    assert(p[4] == 162);
    assert(p[5] == 8364);
    assert(p[6] == 128578);

    // Encode
    std::string s1(4 * n, 0);
    auto k = utf8::Encode(p, s1);
    assert(k > 0);
    s1.resize(k);
    assert(s == s1);
}

int main(void) {
    test1();
    test2();
    return 0;
}
