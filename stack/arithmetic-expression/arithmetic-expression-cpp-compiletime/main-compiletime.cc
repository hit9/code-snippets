// 双栈法 算术表达式求值 - C++ 版本 (编译期计算)
// 支持多位整数
// 编译选项: -std=c++20
// 博客 - 算术表达式求值（双栈法）
// https://writings.sh/post/arithmetic-expression
#include <algorithm>
#include <cstddef>

// Complie-time stack.
template <typename T, size_t N>
class stack {
   private:
    T s[N] = {0};
    int k = 0;

   public:
    constexpr stack() = default;
    constexpr void push(T v) { s[k++] = v; }
    constexpr bool empty() const { return k == 0; }
    constexpr T top() const { return s[k - 1]; }
    constexpr T pop() { return s[--k]; }
};

// Complie-time fixed string.
template <size_t N>
class string {
   public:
    char a[N];
    constexpr string(const char (&s)[N]) { std::copy_n(s, N, a); }
    constexpr size_t size() const { return N; }
    constexpr char operator[](int x) const { return a[x]; }
};

constexpr int to_int(char ch) { return ch - '0'; }
constexpr bool isdigit(char ch) { return ch >= '0' and ch <= '9'; }

constexpr bool is_operator(char op) {
    switch (op) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}

constexpr int operator_priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

constexpr int calculate(char op, int left, int right) {
    switch (op) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        default:
            return 0;
    }
}

template <size_t N>
constexpr void calc(stack<int, N>& nums, stack<char, N>& ops) {
    if (ops.empty()) return;
    auto op = ops.pop();
    auto right = nums.pop();
    auto left = nums.pop();
    nums.push(calculate(op, left, right));
}

template <string s>
constexpr int evaluate() {
    const auto n = s.size();

    stack<int, n> nums;
    stack<char, n> ops;

    nums.push(0);

    int i = 0;

    while (i < n) {
        char x = s[i++];
        if (isdigit(x)) {
            int v = to_int(x);
            while (i < n && isdigit(s[i])) {
                v = v * 10 + to_int(s[i]);
                i++;
            }
            nums.push(v);
        } else if (is_operator(x)) {
            while (!ops.empty() && is_operator(ops.top()) &&
                   operator_priority(ops.top()) >= operator_priority(x)) {
                calc(nums, ops);
            }
            ops.push(x);
        } else if (x == '(') {
            ops.push(x);
        } else if (x == ')') {
            while (!ops.empty() && ops.top() != '(') {
                calc(nums, ops);
            };
            ops.pop();  // 弹出左括号
        }
    }

    // 把栈内剩余运算执行完
    while (!ops.empty()) calc(nums, ops);
    return nums.pop();
}

int main(void) {
    // 应该编译通过
    static_assert(evaluate<"">() == 0);
    static_assert(evaluate<"1+3*2-2">() == 5);
    static_assert(evaluate<"5-6*2+10">() == 3);
    static_assert(evaluate<"">() == 0);
    static_assert(evaluate<"1">() == 1);
    static_assert(evaluate<"()">() == 0);
    static_assert(evaluate<"(16)">() == 16);
    static_assert(evaluate<"(1+2)*3">() == (1 + 2) * 3);
    static_assert(evaluate<"1+2*3+4*5">() == (1 + 2 * 3 + 4 * 5));
    static_assert(evaluate<"5-6*1+2">() == 1);
    static_assert(evaluate<"1+2*3+4*5/3">() == (1 + 2 * 3 + 4 * 5 / 3));
    static_assert(evaluate<"1+(2+2)*3 + (3+2)*2+3+3">() ==
                  1 + (2 + 2) * 3 + (3 + 2) * 2 + 3 + 3);
    static_assert(evaluate<"23 *100 +2 *1+2">() == 23 * 100 + 2 * 1 + 2);
    static_assert(evaluate<"3+2*3*4+2+1">() == 3 + 2 * 3 * 4 + 2 + 1);
    static_assert(evaluate<"2*27-28*2+2+1+6/3">() ==
                  2 * 27 - 28 * 2 + 2 + 1 + 6 / 3);
    return 0;
}
