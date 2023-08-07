// NFA 识别一个简单的浮点数
// 合法例子: '31.25' '0.2' '.2'  '1.'  '-5.28'  '+1.2' '1.0'
// 非法例子: '-.'  '-'  '+'  '-.5' '+-1'   '1.1.1'  '' '.'
//
// 对应的正则表达式 (其中点不是任意的意思，是小数点; 问号表示可选)
// ((+|-)[0-9])?[0-9]*(([0-9].)|(.0-8))?[0-9]*

#include <cassert>
#include <string>

bool IsDigit(char ch) { return ch >= '0' && ch <= '9'; }

// NFA 跳转函数
// 共 9 个状态:
// 0 是初始状态
// 8 是唯一终态
int Jump(int state, char ch, bool is_end) {
    switch (state) {
        case 0:
            if (ch == '+' || ch == '-') return 1;
            return Jump(2, ch, is_end);
        case 1:
            if (IsDigit(ch)) return 2;
            return -1;
        case 2:
            return Jump(3, ch, is_end);
        case 3:
            if (IsDigit(ch)) return 4;
            if (ch == '.') return 6;
            return Jump(5, ch, is_end);
        case 4:
            if (IsDigit(ch)) return 3;
            if (ch == '.') return 5;
            return -1;
        case 5:
            return Jump(7, ch, is_end);
        case 6:
            if (IsDigit(ch)) return 5;
            return -1;
        case 7:
            if (is_end) return 8;
            if (IsDigit(ch)) return 7;
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
    return state == 8;
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
