// 字符串的全排列打印 （去重版本）

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void Swap(char s[], int i, int j) {
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}

void Permute(char s[], int start, int end) {
    if (start == end) {
        printf("%s\n", s);
        return;
    }

    bool m[256] = {false};

    for (int i = start; i <= end; i++) {
        if (m[s[i]]) continue;
        m[s[i]] = true;

        Swap(s, start, i);
        Permute(s, start + 1, end);
        Swap(s, start, i);

    }
}

void PrintPermutations(char s[]) {
    int n = strlen(s);
    Permute(s, 0, n - 1);
}

int main(void) {
    char s1[] = "abc";
    char s2[] = "abb";
    PrintPermutations(s1);
    PrintPermutations(s2);
    return 0;
}
