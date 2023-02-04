// 基本数论类算法
// https://writings.sh/post/algorithm-number-theory

#include <assert.h>
#include <stdbool.h>  // for bool
#include <stdio.h>    // for printf

// 辗转相除法 - 最大公约数
int Gcd(int a, int b) {
    if (a < b) return Gcd(b, a);
    if (b > 0) return Gcd(b, a % b);
    return a;
}

// 辗转相除法 - 最大公约数 - 循环版本
int Gcd_(int a, int b) {
    if (a < b) return Gcd_(b, a);
    while (b > 0) {
        int m = a % b;
        a = b;
        b = m;
    }
    return a;
}

// 最小公倍数
int Lcm(int a, int b) { return a * b / Gcd(a, b); }

// 素数判断
bool IsPrime(int a) {
    if (a < 2) return false;
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) return false;
    }
    return true;
}

// 埃拉托斯特尼筛法
// 输入上限整数 n 和 大小为 n 的筛表
// 筛表中位置为素数的项会被设置 true
void Eratosthenes(int n, bool table[]) {
    if (n <= 0) return;

    for (int i = 0; i < n; i++) table[i] = true;

    if (n >= 1) table[0] = false;
    if (n >= 2) table[1] = false;

    for (int i = 2; i * i < n; i++) {
        if (table[i]) {
            for (int j = i * i; j < n; j += i) table[j] = false;
        }
    }
    return;
}

// 快速素数筛法 - 欧拉筛法
// 输入上限整数 n 、大小为 n 的筛表 table 和 接收返回结果的素数表 primes.
void EulerSieve(int n, bool table[], int primes[]) {
    if (n <= 0) return;

    for (int i = 0; i < n; i++) table[i] = true;

    if (n >= 1) table[0] = false;
    if (n >= 2) table[1] = false;

    int j = 0;  // 记录已知素数的多少
    for (int i = 0; i < n; i++) primes[i] = 0;

    for (int k = 2; k < n; k++) {
        if (table[k]) primes[j++] = k;

        for (int i = 0; i < j; i++) {
            int p = primes[i];

            if (p * k < n)
                table[p * k] = false;
            else
                break;

            if (k % p == 0) break;
        }
    }
    return;
}

int main(void) {
    assert(Gcd(54, 24) == 6);
    assert(Gcd(24, 54) == 6);
    assert(Gcd(1071, 462) == 21);
    assert(Gcd_(54, 24) == 6);
    assert(Gcd_(24, 54) == 6);
    assert(Gcd_(1071, 462) == 21);
    assert(Lcm(54, 24) == 216);
    assert(IsPrime(2) == true);
    assert(IsPrime(18) == false);
    assert(IsPrime(7) == true);
    assert(IsPrime(71) == true);
    assert(IsPrime(131) == true);
    assert(IsPrime(172832) == false);

    bool table[20];
    Eratosthenes(20, table);
    for (int i = 0; i < 20; i++) {
        if (table[i]) printf("%d ", i);
    }
    printf("\n");

    int primes[20];
    EulerSieve(20, table, primes);
    for (int i = 0; i < 20 && primes[i] != 0; i++) {
        printf("%d ", primes[i]);
    }
    printf("\n");
    return 0;
}
