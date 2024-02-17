#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdlib>

using ll = unsigned long long;

int josephus1(int n, int k) {
    int f = 0;
    for (int i = 2; i <= n; i++) {
        f = (f + k) % i;
    }
    return f;
}

int josephus2(int n, int k) {
    if (n == 1) return 0;
    if (k == 1) return n - 1;
    if (k > n) return (josephus2(n - 1, k) + k) % n;
    int f = josephus2(n - n / k, k) - n % k;
    return f + (f < 0 ? n : (f / (k - 1)));
}

int josephus3(int n, int k, ll q) {
    if (k == 1) return n - 1;
    for (q = q * k + k - 1; q >= n; q = q - n + (q - n) / (k - 1))
        ;
    return q;
}

TEST_CASE("Josephus benchmark small k", "[small k]") {
    int k = std::rand() % 63;
    int n = std::rand() % 10000 + 1000000;
    BENCHMARK("josephus1") { return josephus1(n, k); };
    BENCHMARK("josephus2") { return josephus2(n, k); };
    BENCHMARK("josephus3") { return josephus3(n, k, n - 1); };
}

TEST_CASE("Josephus benchmark large k", "[large k]") {
    int n = std::rand() % 10000 + 1000000;
    int k = (std::rand() % 5 + 1) * n + std::rand() % 100000;
    BENCHMARK("josephus1") { return josephus1(n, k); };
    BENCHMARK("josephus2") { return josephus2(n, k); };
    BENCHMARK("josephus3") { return josephus3(n, k, n - 1); };
}
