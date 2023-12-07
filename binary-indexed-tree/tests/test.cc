#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <cstdlib>
#include <numeric>
#include <vector>

#include "bit-max.hpp"
#include "bit-sum.hpp"

using namespace bit;
using namespace std;

TEST_CASE("bit sum", "[bit sum simple 1.]") {
    int n = 1024;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = rand() % 65535;

    BIT b(n);
    for (int i = 1; i <= n; i++) b.add(i, a[i]);

    auto a1 = a.begin() + 1;

    REQUIRE(b.ask(n) == accumulate(a1, a.end(), 0));
    REQUIRE(b.ask(512) == accumulate(a1, a1 + 512, 0));

    int d = rand() % 65535;
    a[512] += d;
    b.add(512, d);
    REQUIRE(b.ask(512) == accumulate(a1, a1 + 512, 0));
    REQUIRE(b.ask(38, 888) == accumulate(a1 + 38 - 1, a1 + 888, 0));
}

TEST_CASE("bit max", "[bit max simple 1.]") {
    int n = 1024;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = rand() % 65535;

    BIT1 b(n);
    for (int i = 1; i <= n; i++) b.update(i, a[i]);

    auto a1 = a.begin() + 1;

    REQUIRE(b.ask(1, n) == *max_element(a1, a1 + n));
    REQUIRE(b.ask(1, 512) == *max_element(a1, a1 + 512));

    int v = rand() % 65535 + *max_element(a1, a1 + 512);
    a[512] = v;
    b.update(512, v);

    REQUIRE(b.ask(1, 512) == *max_element(a1, a1 + 512));
    REQUIRE(b.ask(38, 888) == *max_element(a1 + 38 - 1, a1 + 888));
}
