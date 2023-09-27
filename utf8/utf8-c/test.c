#include <assert.h>
#include <string.h>

#include "utf8.h"

int main(void) {
    const char *s1 = "落花流水a";
    // Count
    size_t n1 = utf8_count((unsigned char *)s1, strlen(s1));
    assert(n1 == 5);
    // Decode
    uint32_t p1[n1];
    assert(utf8_decode((unsigned char *)s1, strlen(s1), p1) == n1);
    assert(p1[0] == 33853);  // 落
    assert(p1[1] == 33457);  // 花
    assert(p1[2] == 27969);  // 流
    assert(p1[3] == 27700);  // 水
    assert(p1[4] == 97);     // a
    // Encode
    char s2[4 * n1];
    size_t k = utf8_encode(p1, n1, (unsigned char *)s2);
    assert(k > 0);
    s2[k] = '\0';
    assert(strcmp(s1, s2) == 0);
    return 0;
}
