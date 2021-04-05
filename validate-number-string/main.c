// 校验表示数值的字符串
// https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/

#include <assert.h>   // for assert
#include <stdbool.h>  // for bool
#include <stdlib.h>   // for NULL

// 状态机的做法
//
// 0 初始状态
// 1 数值符号
// 2 整数
// 3 小数点 - 前置有数字
// 4 小数部分
// 5 字符 e 或  E
// 6 幂数符号
// 7 幂数
// 8 末尾空格
// 9 小数点 - 前置无数字

// 判断字符 ch 是否是数字
bool is_number_letter(char ch) {
    int d = ch - '0';
    if (d >= 0 && d <= 9) return true;
    return false;
}

// 状态跳转，输入当前状态、输入字符、是否结束
// 返回非负的状态。
// 如果禁止跳转，返回 -1
int jump(int state, char ch, bool end) {
    switch (state) {
        case 0:                  // 初始状态
            if (end) return -1;  // 开始即结束，判否
            if (ch == '+' || ch == '-') return 1;
            if (is_number_letter(ch)) return 2;
            if (ch == '.') return 9;  // e.g. ".1"
            if (ch == ' ') return 0;  // 忽略前置空格 e.g. " 1"
            return -1;
        case 1:  // 符号状态
            if (end) return -1;
            if (is_number_letter(ch)) return 2;
            if (ch == '.') return 9;  // e.g. "-.1"
            return -1;
        case 2:                                    // 整数部分
            if (end) return 0;                     // 允许结束
            if (is_number_letter(ch)) return 2;    // 重复此状态
            if (ch == '.') return 3;               // 小数点
            if (ch == 'e' || ch == 'E') return 5;  // 进入科学计数
            if (ch == ' ') return 8;               // 末尾空格
            return -1;
        case 3:                                    // 前置有数字小数点
            if (end) return 0;                     // 允许结束 e.g. "3."
            if (is_number_letter(ch)) return 4;    // 小数部分
            if (ch == 'e' || ch == 'E') return 5;  // 例如奇怪的 "3.e3"
            if (ch == ' ') return 8;               // 例如 "3. "
            return -1;
        case 9:                                  // 前置无数字小数点
            if (end) return -1;                  // 不允许结束 e.g. "."
            if (is_number_letter(ch)) return 4;  // 小数部分
            return -1;
        case 4:                                  // 小数部分
            if (end) return 0;                   // 允许结束
            if (is_number_letter(ch)) return 4;  // 重复小数
            if (ch == 'e' || ch == 'E')
                return 5;  // 还有这种神奇的  ".2e81" 的数字
            if (ch == ' ') return 8;
            return -1;
        case 5:                                    // e/E
            if (end) return -1;                    // 不许结束
            if (ch == '+' || ch == '-') return 6;  // 幂符号
            if (is_number_letter(ch)) return 7;    // 幂数
            return -1;
        case 6:                                  // 幂数符号
            if (end) return -1;                  // 不许结束
            if (is_number_letter(ch)) return 7;  // 幂数
            return -1;
        case 7:                                  // 幂数
            if (end) return 0;                   // 允许结束
            if (is_number_letter(ch)) return 7;  // 重复幂数
            if (ch == ' ') return 8;
            return -1;
        case 8:                       // 末尾空格
            if (end) return 0;        // 允许结束
            if (ch == ' ') return 8;  // 重复末尾空格
            return -1;
        default:
            return -1;
    }
}

// 判断字符串是否是数字
// 合法的例子: "+100"  "5e2"  "1.1"  "-1E-16"  ".3"  "1 "  ".3"  "3.e2"  " +32"
// 非法的例子: "1 2e"  "1.2.3"  "1a3.1"  "12e+32"
bool IsNumberic(char *s) {
    if (s == NULL) return false;
    int state = 0;  // 初始状态 0
    int i = 0;
    while (1) {
        char ch = s[i++];
        bool end = false;
        if (ch == '\0') end = true;

        state = jump(state, ch, end);

        if (state < 0) return false;
        if (end) break;
    }
    return true;
}

int main(void) {
    assert(IsNumberic("123"));
    assert(IsNumberic("+123"));
    assert(IsNumberic("5e2"));
    assert(IsNumberic("+5e2"));
    assert(IsNumberic("  1"));
    assert(IsNumberic("  1.2"));
    assert(IsNumberic(".2  "));
    assert(IsNumberic("3.e2"));
    assert(IsNumberic("+32.23"));
    assert(IsNumberic("12.23"));
    assert(IsNumberic(".1"));
    assert(IsNumberic(".1 "));
    assert(!IsNumberic("."));
    assert(!IsNumberic(" ."));
    assert(IsNumberic(" 1."));
    assert(IsNumberic(" .334 "));
    assert(IsNumberic("-1E-16"));
    assert(IsNumberic("0123"));
    assert(!IsNumberic("+0ab"));
    assert(!IsNumberic("+-7"));
    assert(!IsNumberic("12e+3.2"));
    return 0;
}
