// 基本数学运算类算法 - 加减乘除
// https://writings.sh/post/algorithm-basic-math-computations

#include <assert.h>
#include <limits.h>
#include <stdio.h>  // for printf

// 加法
int Add(int a, int b) {
    do {
        int c = (unsigned int)(a & b) << 1;
        int s = a ^ b;
        a = c;
        b = s;
    } while (a != 0);
    return b;
}

// 减法
int Minus(int a, int b) { return Add(a, Add(~b, 1)); }

#define MIN(a, b) (a) > (b) ? (b) : (a)
#define MAX(a, b) (a) > (b) ? (a) : (b)

// 乘法 - 简单方法 O(min(a,b))
// 假设加法已经实现
int MulNaive(int a, int b) {
    if (a == 0 || b == 0) return 0;
    if (a < 0 && b < 0) return MulNaive(-a, -b);
    if (a < 0 && b > 0) return -MulNaive(-a, b);
    if (a > 0 && b < 0) return -MulNaive(a, -b);

    // Now, both a and b are positive numbers.
    int min = MIN(a, b);
    int max = MAX(a, b);
    int r = 0;

    while (min-- != 0) r += max;
    return r;
}

// 乘法 - 二分法递归版本
int MulRecursive(int a, int b) {
    if (a == 0 || b == 0) return 0;
    if (a < 0 && b < 0) return MulRecursive(-a, -b);
    if (a < 0 && b > 0) return -MulRecursive(-a, b);
    if (a > 0 && b < 0) return -MulRecursive(a, -b);

    int min = MIN(a, b);
    int max = MAX(a, b);

    if (min & 1)  // 奇数
        return MulRecursive(min - 1, max) + max;
    else {  // 偶数, 注意 min/2 即 min >> 1
        int half = MulRecursive(min >> 1, max);
        return half << 1;  // 即 half x 2
    }
}

// 乘法 - 二分法循环版本
int MulBinary(int a, int b) {
    if (a == 0 || b == 0) return 0;
    if (a < 0 && b < 0) return MulBinary(-a, -b);
    if (a < 0 && b > 0) return -MulBinary(-a, b);
    if (a > 0 && b < 0) return -MulBinary(a, -b);

    int min = MIN(a, b);  // 小的作倍数
    int max = MAX(a, b);  // 大的作被乘数

    int r = 0;         // 计算结果
    int factor = max;  // 乘积因子
    int remain = min;  // 剩余倍数

    while (remain != 0) {
        if (remain & 1) {
            // 剩余倍数为奇数
            r += factor;
            remain--;
        } else {
            remain >>= 1;  // 剩余倍数缩小一半
            factor <<= 1;  // 被乘数扩大两倍
        }
    }
    return r;
}

// 乘法 - 竖式计算方法
int MulFast(int a, int b) {
    if (a == 0 || b == 0) return 0;
    if (a < 0 && b < 0) return MulFast(-a, -b);
    if (a < 0 && b > 0) return -MulFast(-a, b);
    if (a > 0 && b < 0) return -MulFast(a, -b);

    int r = 0;  // 乘法结果

    while (a != 0) {
        if (a & 1) {
            // 当前位是 1, 1 乘以任何数为自身
            // 加上此时的 b
            r += b;
        }
        // 否则，当前位是 0， 0 乘以任何数是 0, 无需加上

        a >>= 1;  // 移动 n 次到 0 意味着 a 有 n 个比特位
        b <<= 1;  // 同步左移 b
    }
    return r;
}

// 除法 a / b
int Div(int a, int b) {
    if (a == 0) return 0;
    if (b == 0) return -1;

    // 转为正数计算
    if (a < 0 && b < 0) return Div(-a, -b);
    if (a < 0 && b > 0) return -Div(-a, b);
    if (a > 0 && b < 0) return -Div(a, -b);

    int remain = a;
    int factor = 1;
    int bfactor = b;  // b x factor.
    int result = 0;

    while (remain >= b) {
        if (remain < bfactor) {
            // 被除数不足以相减，重置 factor
            factor = 1;
            bfactor = b;
        }

        remain -= bfactor;
        result += factor;

        // factor x2
        factor = factor << 1;
        // bfactor x2
        bfactor = bfactor << 1;
    }
    return result;
}

// 获取给定整数的比特位数
int GetNBits(int a) {
    int n = 0;
    while (a) {
        a >>= 1;
        n++;
    }
    return n;
}

// 除法 竖式计算
int DivFast(int a, int b) {
    if (a == 0) return 0;
    if (b == 0) return -1;

    // 转为正数计算
    if (a < 0 && b < 0) return DivFast(-a, -b);
    if (a < 0 && b > 0) return -DivFast(-a, b);
    if (a > 0 && b < 0) return -DivFast(a, -b);

    int n = GetNBits(a);
    int m = GetNBits(b);

    int r = 0;  // 计算结果

    for (int i = n - m; i >= 0; i--) {
        // 左移 b 对齐当前的 a
        int b1 = b << i;
        if (b1 <= a) {
            // 标记结果的第 i 位为 1
            r |= (1 << i);
            a -= b1;
        }
        // 否则，是 0，不用设置
    }

    return r;
}

// 幂运算 - 二分 递归版本
// 以下只考虑正数实现，负数可转正数处理
int PowRecursive(int a, int b) {
    if (b == 0) return 1;
    // 奇数
    if (b & 1) return PowRecursive(a, b - 1) * a;
    // 偶数
    else {
        int half = PowRecursive(a, b / 2);
        return half * half;
    }
}

// 幂运算 - 二分 循环版本
// 以下只考虑正数实现，负数可转正数处理
int PowFast(int a, int b) {
    int factor = a;
    int result = 1;
    int remain = b;
    while (remain > 0) {
        if (remain & 1) {
            // 奇数
            result = result * factor;
            remain--;
        } else {
            // 偶数
            remain = remain / 2;       // 剩余指数拆半
            factor = factor * factor;  // 因子自乘翻倍
        }
    }
    return result;
}

// 幂运算 - 二分 循环版本 ( 带 mod )
// 以下只考虑正数实现，负数可转正数处理
int PowFastMod(int a, int b, int mod) {
    int factor = a % mod;
    int result = 1;
    int remain = b;
    while (remain > 0) {
        if (remain & 1) {
            // 奇数
            result = result * factor % mod;
            remain--;
        } else {
            // 偶数
            remain = remain / 2;  // 剩余指数拆半
            factor = factor * factor % mod;
            ;  // 因子自乘翻倍
        }
    }
    return result % mod;
}
// 平方根运算 - 二分
// a 为非负数
int Sqrt(int a) {
    if (a == 0) return 0;
    if (a == 1) return 1;

    int l = 0;
    int r = a;

    while (l < r) {
        int m = (l + r) / 2;
        if (m < a / m) {  // 不采用 m * m < a 防止溢出
            l = m + 1;
        } else if (m > a / m) {
            r = m - 1;
        } else {
            return m;
        }
    }

    // 找到的 l 有可能比实际值稍大
    if (l > a / l) return l - 1;

    return l;
}

// 平方根运算 - 牛顿法
// a 为非负数
int SqrtNewton(int a) {
    if (a == 0) return 0;

    double x = a;  // 初始值起为 a 本身
    double d = 0.0;

    do {
        // delta 是 f(x) / f'(x)
        // 即 (x^2 - a) / (2x)
        // 防溢出，写作如下方式
        d = x / 2 - a / x / 2.0;
        if (d < 1e-6) break;  // 假设误差是 1e-6
        x -= d;
    } while (x - a / x > 0);

    return x;
}

int main(void) {
    assert(Add(1, 2) == 3);
    assert(Add(878, 179) == 1057);
    assert(Add(-1, 2) == 1);
    assert(Add(-7777, -1234) == -9011);

    assert(Minus(156, 78) == 78);
    assert(Minus(-1, 78) == -79);
    assert(Minus(-1, -222) == 221);

    assert(MulNaive(3, 4) == 12);
    assert(MulNaive(3456, 22344) == 77220864);
    assert(MulNaive(-1, 1234) == -1234);
    assert(MulNaive(-22, 12356) == -271832);
    assert(MulNaive(-22, -12356) == 271832);

    assert(MulRecursive(3, 4) == 12);
    assert(MulRecursive(3456, 22344) == 77220864);
    assert(MulRecursive(-1, 1234) == -1234);
    assert(MulRecursive(-22, 12356) == -271832);
    assert(MulRecursive(-22, -12356) == 271832);

    assert(MulBinary(3, 4) == 12);
    assert(MulBinary(3456, 22344) == 77220864);
    assert(MulBinary(-1, 1234) == -1234);
    assert(MulBinary(-22, 12356) == -271832);
    assert(MulBinary(-22, -12356) == 271832);

    assert(MulFast(3, 4) == 12);
    assert(MulFast(3456, 22344) == 77220864);
    assert(MulFast(-1, 1234) == -1234);
    assert(MulFast(-22, 12356) == -271832);
    assert(MulFast(-22, -12356) == 271832);

    assert(Div(12, 4) == 3);
    assert(Div(12, 5) == 2);
    assert(Div(225, 17) == 13);
    assert(Div(77220866, 3456) == 22344);
    assert(Div(-1, -1) == 1);
    assert(Div(-1, -98) == 0);
    assert(Div(-111111, 335) == -331);

    assert(DivFast(12, 4) == 3);
    assert(DivFast(12, 5) == 2);
    assert(DivFast(225, 17) == 13);
    assert(DivFast(77220866, 3456) == 22344);
    assert(DivFast(-1, -1) == 1);
    assert(DivFast(-1, -98) == 0);
    assert(DivFast(-111111, 335) == -331);

    assert(PowRecursive(3, 13) == 1594323);
    assert(PowRecursive(1, 1024) == 1);
    assert(PowRecursive(2, 10) == 1024);
    assert(PowFast(3, 13) == 1594323);
    assert(PowFast(1, 1024) == 1);
    assert(PowFast(2, 10) == 1024);

    assert(Sqrt(2) == 1);
    assert(Sqrt(4) == 2);
    assert(Sqrt(36) == 6);
    assert(Sqrt(81) == 9);
    assert(Sqrt(23) == 4);
    assert(Sqrt(361) == 19);

    assert(SqrtNewton(2) == 1);
    assert(SqrtNewton(4) == 2);
    assert(SqrtNewton(36) == 6);
    assert(SqrtNewton(81) == 9);
    assert(SqrtNewton(23) == 4);
    assert(SqrtNewton(361) == 19);
}
