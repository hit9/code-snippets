#include <bitset>
#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <random>

#include "segbitset.h"

static const std::size_t N_1M_BITS = 8192;
static std::mt19937 rng(std::random_device{}());

TEST_CASE("benchmark/sparse/1", "benchmarks on sparse dataset") {
  std::uniform_int_distribution<std::size_t> distribution(0, N_1M_BITS - 1);
  // when about 1/50 bits  (about 2%) are set, segbitset performs faster..
  std::bitset<N_1M_BITS> b;
  for (int i = 0; i < N_1M_BITS / 30.0; i++) {
    auto j = distribution(rng);
    b.set(j);
  }
  segbitset::segbitset<N_1M_BITS> s(b);

  //////////////////////////////////////////////////////////////
  /// Find positions of true bits
  //////////////////////////////////////////////////////////////

  size_t cnt = 0;  // avoid compiler optimization away
  BENCHMARK("segbitset - first and next") {
    for (std::size_t pos = s.first(); pos != s.size(); pos = s.next(pos)) ++cnt;
  };

  segbitset::callback cb = [&](std::size_t pos) { ++cnt; };

  BENCHMARK("segbitset - foreach") { s.foreach1(cb); };

  BENCHMARK("stdbitset - for true bits") {
    for (std::size_t pos = 0; pos != b.size(); pos++)
      if (b[pos]) ++cnt;
  };
}

TEST_CASE("benchmark/bitset and vector") {
  std::uniform_int_distribution<std::size_t> distribution(0, N_1M_BITS - 1);

  std::bitset<N_1M_BITS> b;
  std::vector<int> x;
  for (int i = 0; i < N_1M_BITS / 10.0; i++) {
    auto j = distribution(rng);
    if (!b[j]) {
      x.push_back(j);
      b.set(j);
    }
  }

  size_t cnt = 0;  // avoid compiler optimization away
  BENCHMARK("bitset") {
    for (std::size_t pos = 0; pos != b.size(); pos++)
      if (b[pos]) ++cnt;
  };
  BENCHMARK("vector") {
    for (auto i : x) cnt+=i;
  };
}
