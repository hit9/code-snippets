// DFA 识别一个简单的浮点数
// 合法例子: '31.25' '0.2' '.2'  '1.'  '-5.28'  '+1.2' '1.0' '123'
// 非法例子: '-.'  '-'  '+'  '-.5' '+-1'   '1.1.1'  '' '.'
// 博客 - 自动机校验浮点数字符串 (DFA & NFA)
// https://writings.sh/post/statemachine-validate-float

#include <cassert>
#include <string>

bool IsDigit(char ch) { return ch >= '0' && ch <= '9'; }

// DFA 跳转函数
// 共 6 个状态:
// 0 是初始状态
// 2, 4, 5 是终态
// 返回 6 表示正确跳到终态
// 0 号状态  等待第一个字符，可能是数字, 小数点 或者 +- 号
// 1 号状态  输入正负号后，等待输入数字的状态
// 4 号状态  输入正负号后，已经输入数字的状态
// 2 号状态  整数部分循环输入数字的状态
// 3 号状态  第一位或者第二位输入小数点后的状态
// 5 号状态  输入小数点后循环输入数字的状态，同时是终态
int Jump(int state, char ch, bool is_end) {
    switch (state) {
        case 0:
            if (ch == '+' || ch == '-') return 1;
            if (ch == '.') return 3;
            if (IsDigit(ch)) return 2;
            return -1;
        case 1:
            if (IsDigit(ch)) return 4;
            return -1;
        case 2:
            if (is_end) return 6;
            if (ch == '.') return 5;
            if (IsDigit(ch)) return 2;
            return -1;
        case 3:
            if (IsDigit(ch)) return 5;
            return -1;
        case 4:
            if (is_end) return 6;
            if (ch == '.') return 3;
            if (IsDigit(ch)) return 2;
            return -1;
        case 5:
            if (is_end) return 6;
            if (IsDigit(ch)) return 5;
            return -1;
        default:
            return -1;
    }
}

bool IsFloat(const std::string& s) {
    if (s.size() == 0) return false;
    int state = 0;

    for (auto& ch : s) {
        state = Jump(state, ch, false);
        if (state == -1) return false;
    }
    state = Jump(state, '\0', true);
    return state == 6;
}

int main(void) {
    assert(IsFloat("3.14"));
    assert(!IsFloat(""));
    assert(IsFloat("31.25"));
    assert(IsFloat("0.2"));
    assert(IsFloat("-1.2"));
    assert(IsFloat("+1.2"));
    assert(IsFloat("1."));
    assert(IsFloat("-5.28"));
    assert(IsFloat(".0"));
    assert(IsFloat("1.0"));
    assert(IsFloat("123"));
    assert(IsFloat("+3"));
    assert(IsFloat("-123"));
    assert(!IsFloat("+"));
    assert(!IsFloat("-"));
    assert(!IsFloat("-."));
    assert(!IsFloat("+."));
    assert(!IsFloat("+ "));
    assert(!IsFloat("-.5"));
    assert(!IsFloat("-+1"));
    assert(!IsFloat("+-1"));
    assert(!IsFloat("1.1.1"));
    assert(!IsFloat("."));
    return 0;
}
