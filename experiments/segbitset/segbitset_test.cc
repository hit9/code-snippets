#include "segbitset.h"

#include <bitset>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <random>

static std::mt19937 rng(std::random_device{}());

template <std::size_t N>
void random_fill_bitset(std::bitset<N>& b) {
  std::uniform_int_distribution<std::size_t> distribution(0, N - 1);
  for (int i = 0; i < N / 2; i++) {
    auto j = distribution(rng);
    b.set(j);
  }
}

template <std::size_t N>
void random_fill_segbitset(segbitset::segbitset<N>& s) {
  std::uniform_int_distribution<std::size_t> distribution(0, N - 1);
  for (int i = 0; i < N / 2; i++) {
    auto j = distribution(rng);
    s.set(j);
  }
}

template <std::size_t N>
std::bitset<N> make_random_bitset() {
  std::bitset<N> b;
  random_fill_bitset(b);
  return b;
}

template <std::size_t N>
segbitset::segbitset<N> make_random_segbitset() {
  segbitset::segbitset<N> s;
  random_fill_segbitset<N>(s);
  return s;
}

static inline const std::size_t N_1G_BITS = 1024 * 1024 * 1024;  // 1G bits

TEST_CASE("build", "[build from std::bitset]") {
  auto b = make_random_bitset<1024>();
  segbitset::segbitset<1024> s(b);
  for (int i = 0; i < 1024; i++) REQUIRE(b[i] == s[i]);
}

TEST_CASE("tobitset", "[convert to std::bitset]") {
  auto b = make_random_bitset<1024>();
  segbitset::segbitset<1024> s(b);
  REQUIRE(b == s.to_bitset());
}

TEST_CASE("tobitset", "[fill into existing std::bitset]") {
  auto b = make_random_bitset<1024>();
  segbitset::segbitset<1024> s(b);
  std::bitset<1024> b1;
  s.to_bitset(b1);
  REQUIRE(b == b1);
}

TEST_CASE("copy", "[copy constructor]") {
  auto s = make_random_segbitset<1024>();
  decltype(s) s1(s);  // copy constructor.
  REQUIRE(s == s1);
}

TEST_CASE("copy", "[copy assign operatopr]") {
  auto s = make_random_segbitset<1024>();
  auto s1 = s;
  REQUIRE(s == s1);
}

TEST_CASE("size", "[size]") {
  auto s = make_random_segbitset<1024>();
  REQUIRE(s.size() == 1024);
}

TEST_CASE("capacity", "[capacity]") {
  auto s = make_random_segbitset<1024>();
  REQUIRE(s.capacity() == 1024 * 2);
}

TEST_CASE("count", "[count simple]") {
  auto s = make_random_segbitset<1024>();
  auto b = s.to_bitset();
  assert(s.count() == b.count());
}

TEST_CASE("count", "[count large set]") {
  auto s = new segbitset::segbitset<N_1G_BITS>();
  auto b = new std::bitset<N_1G_BITS>();
  assert(s->count() == b->count());
  delete b;
  delete s;
}

TEST_CASE("test", "[test]") {
  auto s = make_random_segbitset<1024>();
  auto b = s.to_bitset();
  for (auto i = 0; i < 1024; i++) {
    if (b[i])
      REQUIRE(s.test(i));
    else
      REQUIRE(!s.test(i));
  }
}

TEST_CASE("all", "[all - simple]") {
  segbitset::segbitset<8> s;
  REQUIRE(!s.all());
  s[1] = 1;
  REQUIRE(!s.all());
  for (int i = 0; i < s.size(); i++) s.set(i);
  REQUIRE(s.all());
}

TEST_CASE("all", "[all - compare to bitset]") {
  for (int i = 0; i < 1024; i++) {
    auto s = make_random_segbitset<1024>();
    auto b = s.to_bitset();
    REQUIRE(b.all() == s.all());
  }
}

TEST_CASE("any", "[any - simple]") {
  segbitset::segbitset<8> s;
  REQUIRE(!s.any());
  s[1] = 1;
  REQUIRE(s.any());
}

TEST_CASE("any", "[any - compare to bitset]") {
  for (int i = 0; i < 1024; i++) {
    auto s = make_random_segbitset<1024>();
    auto b = s.to_bitset();
    REQUIRE(b.any() == s.any());
  }
}

TEST_CASE("none", "[none - simple]") {
  segbitset::segbitset<8> s;
  REQUIRE(s.none());
  s[1] = 1;
  REQUIRE(!s.none());
}

TEST_CASE("set", "[set all to true]") {
  segbitset::segbitset<8> s;
  REQUIRE(s.none());
  s.set();
  REQUIRE(s.all());
}

TEST_CASE("set", "[set a single position]") {
  segbitset::segbitset<8> s;
  REQUIRE(!s[1]);
  s.set(1);
  REQUIRE(s[1]);
}

TEST_CASE("reset", "[reset all to false]") {
  segbitset::segbitset<8> s;
  for (int i = 0; i < s.size(); i++) s[i] = 1;
  REQUIRE(!s.none());
  s.reset();
  REQUIRE(s.none());
}

TEST_CASE("flip", "[flip all]") {
  auto s = make_random_segbitset<1024>();
  auto b = s.to_bitset();
  s.flip();
  for (int i = 0; i < 1024; i++) REQUIRE(!s[i] == b[i]);
}

TEST_CASE("flip", "[flip a single position]") {
  segbitset::segbitset<8> s;
  REQUIRE(!s[0]);
  s.flip(0);
  REQUIRE(s[0]);
  s.set(5);
  REQUIRE(s[5]);
  s.flip(5);
  REQUIRE(!s[5]);
}

TEST_CASE("first/next", "[find positions of true bits - simple]") {
  std::bitset<8> b;
  b.set(0);
  b.set(3);
  b.set(5);
  b.set(6);
  segbitset::segbitset<8> s(b);
  REQUIRE(b == s.to_bitset());

  std::size_t pos = 1000000;

  pos = s.first();
  REQUIRE(pos == 0);
  REQUIRE(b[pos]);

  pos = s.next(pos);
  REQUIRE(pos == 3);
  REQUIRE(b[pos]);

  pos = s.next(pos);
  REQUIRE(pos == 5);
  REQUIRE(b[pos]);

  pos = s.next(pos);
  REQUIRE(pos == 6);
  REQUIRE(b[pos]);

  pos = s.next(pos);
  REQUIRE(pos == 8);  // not found
}

TEST_CASE("first/next", "[find positions of true bits - large]") {
  auto b = make_random_bitset<1024>();
  segbitset::segbitset<1024> s(b);
  REQUIRE(b == s.to_bitset());

  std::size_t pos = 1000000;

  // find the first;
  auto i = 0;
  for (; i < 1024; i++)
    if (b[i]) break;

  pos = s.first();
  REQUIRE(pos == i);

  // find the next
  for (i = pos + 1; i < 1024; i++) {
    if (b[i]) {
      REQUIRE(s[i]);
      pos = s.next(pos);
      REQUIRE(pos == i);
    } else {
      REQUIRE(!s[i]);
    }
  }

  pos = s.next(pos);
  REQUIRE(pos == 1024);  // not found
}

TEST_CASE("foreach1", "[iterate each 1 - simple]") {
  std::bitset<8> b;
  b.set(2);
  b.set(6);
  b.set(7);
  segbitset::segbitset<8> s(b);
  REQUIRE(b == s.to_bitset());

  int cnt = 0;
  segbitset::callback cb = [&](std::size_t i) {
    REQUIRE(s[i]);
    cnt++;
  };
  s.foreach1(cb);
  REQUIRE(cnt == 3);
}

TEST_CASE("foreach1", "[iterate each 1 - large]") {
  auto b = make_random_bitset<1024>();
  segbitset::segbitset<1024> s(b);
  REQUIRE(b == s.to_bitset());

  std::size_t pos = 1000000;

  int cnt = 0;
  segbitset::callback cb = [&](std::size_t i) {
    REQUIRE(b[i]);
    REQUIRE(s[i]);
    cnt++;
  };

  s.foreach1(cb);
  REQUIRE(cnt == b.count());
}

TEST_CASE("operator==", "[test operator equal]") {
  segbitset::segbitset<8> s1;
  s1.set(1);
  s1.set(3);
  s1.set(7);
  segbitset::segbitset<8> s2;
  s2.set(1);
  s2.set(3);
  s2.set(7);
  REQUIRE(s1 == s2);
  s2.set(6);
  REQUIRE(s1 != s2);
}

TEST_CASE("operatopr[]", "[test operator get item returns bool]") {
  segbitset::segbitset<8> s;
  s.set(1);
  s.set(3);
  s.set(7);
  REQUIRE(s[1]);
  REQUIRE(!s[2]);
}

TEST_CASE("operatopr[]", "[test operator get item reference set]") {
  segbitset::segbitset<8> s;
  s.set(1);
  s.set(3);
  s.set(7);
  REQUIRE(s[1]);
  s[1] = 0;
  REQUIRE(!s[1]);
}

TEST_CASE("operatopr&=", "[test operator and euqal]") {
  segbitset::segbitset<1024> s1(std::bitset<1024>(123));
  segbitset::segbitset<1024> s2(std::bitset<1024>(456));
  s1 &= s2;
  REQUIRE(s1.to_bitset() == std::bitset<1024>(123 & 456));  // 72
}

TEST_CASE("operatopr|=", "[test operator or euqal]") {
  segbitset::segbitset<1024> s1(std::bitset<1024>(149));
  segbitset::segbitset<1024> s2(std::bitset<1024>(278));
  s1 |= s2;
  REQUIRE(s1.to_bitset() == std::bitset<1024>(149 | 278));  // 407
}

TEST_CASE("operatopr^=", "[test operator xor euqal]") {
  segbitset::segbitset<1024> s1(std::bitset<1024>(111));
  segbitset::segbitset<1024> s2(std::bitset<1024>(233));
  s1 ^= s2;
  REQUIRE(s1.to_bitset() == std::bitset<1024>(111 ^ 233));  // 134
}

TEST_CASE("operatopr~=", "[test operator xor euqal]") {
  segbitset::segbitset<1024> s1(std::bitset<1024>(283));
  auto s2 = ~s1;
  REQUIRE(~s1.to_bitset() == s2.to_bitset());
}

TEST_CASE("operatopr&", "[test operator and: a & b]") {
  segbitset::segbitset<1024> s1(std::bitset<1024>(116));
  segbitset::segbitset<1024> s2(std::bitset<1024>(318));
  segbitset::segbitset<1024> s3(std::bitset<1024>(116 & 318));
  REQUIRE((s1 & s2) == s3);
}

TEST_CASE("operatopr|", "[test operator and: a | b]") {
  segbitset::segbitset<1024> s1(std::bitset<1024>(878));
  segbitset::segbitset<1024> s2(std::bitset<1024>(912));
  segbitset::segbitset<1024> s3(std::bitset<1024>(878 | 912));
  REQUIRE((s1 | s2) == s3);
}

TEST_CASE("operatopr^", "[test operator and: a ^ b]") {
  segbitset::segbitset<1024> s1(std::bitset<1024>(777));
  segbitset::segbitset<1024> s2(std::bitset<1024>(991));
  segbitset::segbitset<1024> s3(std::bitset<1024>(777 ^ 991));
  REQUIRE((s1 ^ s2) == s3);
}
