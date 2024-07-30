// Copyright (c) 2024 Chao Wan
// std::cout << x << std::endl;g <hit9@icloud.com>
// License: BSD. https://github.com/hit9/segbitset
// C++ bitset on segment-tree for better performance on sparse bitsets.
// Version: 0.1.0
//
// Tree structure schematic diagram::
//
//   [                  1                   ]     => root  -+
//   [        1         ][       0          ]               |--> OR summary of descendants
//   [   1    ][   0    ][   0    ][   0    ]              -+
//   [ 1 ][ 0 ][ 0 ][ 0 ][ 0 ][ 0 ][ 0 ][ 0 ]     => bit data itself
//
// Core acceleration points:
//  1. any(),none() just reads root bit's value, O(1)
//  2. quickly skip subtrees that are all 0, for and,or,xor operations.
//  3. find positions storing true bits faster for sparse bits data.
//
// Tradeoffs:
//  1. set(pos),test(pos),flip(pos) now are slower than std::bitset, O(logN).
//  2. occupying x4 times space than an equivalent std::bitset.
//  3. shift operations and to_string/to_ulong aren't implementated yet.

#ifndef __HIT9_SEGBITSET
#define __HIT9_SEGBITSET

#include <algorithm>
#include <bitset>
#include <cstddef>     // for size_t
#include <functional>  // for function
#include <iostream>
#include <stdexcept>

namespace segbitset {

using size_t = std::size_t;

// callback is a function that receives a position as parameter.
using callback = std::function<void(size_t pos)>;

template <size_t N>
class segbitset {
  static const size_t __N = N << 1;
  using __bitset = std::bitset<__N>;  // x2 space, starting from 0
  using __segbitset = segbitset<N>;

 public:
  class reference {  // reference to a bit
   private:
    __segbitset& s;
    const size_t x = 0;
    const size_t pos = 0;

   public:
    constexpr explicit reference(__segbitset& s, size_t x, size_t pos) : s(s), x(x), pos(pos) {}

    constexpr reference& operator=(bool value) noexcept;        // for b[i] = value;
    constexpr reference& operator=(const reference&) noexcept;  // for b[i] = b[j];
    constexpr bool operator~() const noexcept;                  // flips the bit
    constexpr operator bool() const noexcept;                   // for x = b[i];
    constexpr reference& flip() noexcept;                       // for b[i].flip();
  };

  constexpr explicit segbitset() noexcept {}
  // creates a segbitset from a std::bitset
  constexpr segbitset(const std::bitset<N>& a) noexcept;  // cppcheck-suppress noExplicitConstructor
  // copy constructor
  constexpr segbitset(const __segbitset& o) noexcept;  // cppcheck-suppress noExplicitConstructor

  // returns the number of bits that this segbitset holds
  constexpr size_t size() const noexcept { return N; }
  // returns the capacity of bits this segbitset occupies.
  constexpr size_t capacity() const noexcept { return tree.size(); }
  // returns the number of bits set to true
  constexpr size_t count() const noexcept;

  // returns the value of the bit at the position pos (counting from 0).
  // throws std::out_of_range if pos is invalid.
  constexpr bool test(size_t pos) const;
  // checks if all of the bits are set to true
  constexpr bool all() const noexcept;
  // checks if any of the bits are set to true
  constexpr bool any() const noexcept;
  // checks if none of the bits are set to true
  constexpr bool none() const noexcept;
  // sets all bits to true.
  constexpr __segbitset& set() noexcept;
  // sets the bit at position pos to the given value.
  // throws std::out_of_range if pos is invalid.
  constexpr __segbitset& set(size_t pos, bool value = true);
  // sets all bits to false.
  constexpr __segbitset& reset() noexcept;
  // sets the bit at position pos to false.
  // throws std::out_of_range if pos is invalid.
  constexpr __segbitset& reset(size_t pos);
  // flips all bits (like operator~, but in-place).
  constexpr __segbitset& flip() noexcept;
  // flips the bit at the position pos.
  // throws std::out_of_range if pos is invalid.
  constexpr __segbitset& flip(size_t pos);
  // find the first position where stores a true bit, returns size of this segbitset if not found.
  constexpr size_t first() const noexcept;
  // find the next position where stores a true bit from the right part of given position, returns size of
  // this segbitset if not found.
  constexpr size_t next(size_t pos) const noexcept;
  // iterates all true bits from left to right and execute given callback function,
  // with the position of true bits as a argument.
  // foreach1 should be faster than first & next, since it dosen't require walking from root again.
  constexpr void foreach1(callback& cb) const noexcept;
  // constructs and returns an equivalent std::bitset from this segbitset.
  constexpr std::bitset<N> to_bitset() const noexcept;
  // fill given std::bitset as an equivalent of this segbitset.
  // the given bitset should be all zero in advance.
  constexpr void to_bitset(std::bitset<N>& a) noexcept;

  constexpr __segbitset& operator=(const __segbitset& o) noexcept;   // copy assign operator
  constexpr bool operator==(const __segbitset& rhs) const noexcept;  // for b == rhs;
  constexpr bool operator!=(const __segbitset& rhs) const noexcept { return !(*this == rhs); }
  // b[pos] returns the value of bit at position pos.
  constexpr bool operator[](size_t pos) const { return test(pos); }
  // b[pos] returns a reference to the bit at position pos.
  constexpr reference operator[](size_t pos);
  constexpr __segbitset& operator&=(const __segbitset& other) noexcept;  // for b &= other
  constexpr __segbitset& operator|=(const __segbitset& other) noexcept;  // for b |= other
  constexpr __segbitset& operator^=(const __segbitset& other) noexcept;  // for b ^= other
  constexpr __segbitset operator~() const noexcept;                      // ~b, returns a copy of flipped b

 private:
  __bitset tree;
  size_t L[__N], SIZES[__N];

  inline constexpr size_t __ls(size_t x) const { return x + 1; }
  inline constexpr size_t __rs(size_t l, size_t m, size_t x) const { return x + ((m - l + 1) << 1); }
  inline constexpr void __pushup(size_t x, size_t y, size_t z) noexcept;
  constexpr void __build(const std::bitset<N>& a, size_t l, size_t r, size_t x) noexcept;
  constexpr size_t __count(size_t l, size_t r, size_t x) const noexcept;
  constexpr size_t __find(size_t pos, size_t l, size_t r, size_t x) const noexcept;  // helper
  constexpr void __set(size_t pos, bool v, size_t l, size_t r, size_t x) noexcept;
  constexpr bool __all(size_t l, size_t r, size_t x) const noexcept;
  constexpr void __flip(size_t l, size_t r, size_t x) noexcept;
  constexpr bool __flip_pos(size_t pos, size_t l, size_t r, size_t x) noexcept;
  constexpr void __reset(size_t l, size_t r, size_t x) noexcept;
  constexpr bool __equal(const __segbitset& rhs, size_t l, size_t r, size_t x) const noexcept;
  constexpr void __copy(const __segbitset& o, size_t l, size_t r, size_t x) noexcept;
  constexpr void __and_assign(const __segbitset& other, size_t l, size_t r, size_t x) noexcept;
  constexpr void __or_assign(const __segbitset& other, size_t l, size_t r, size_t x) noexcept;
  constexpr void __xor_assign(const __segbitset& other, size_t l, size_t r, size_t x) noexcept;
  constexpr void __to_bitset(std::bitset<N>& a, size_t l, size_t r, size_t x) noexcept;
  constexpr void __next(size_t pos, size_t l, size_t r, size_t x, size_t& ans) const noexcept;
  constexpr void __foreach1(callback& cb, size_t l, size_t r, size_t x) const noexcept;

  friend class reference;
};

////// Implementation ///////

template <size_t N>
constexpr void segbitset<N>::__pushup(size_t x, size_t y, size_t z) noexcept {
  tree[x] = tree[y] | tree[z];
  SIZES[x] = SIZES[y] + SIZES[z] + 1;
}

template <size_t N>
constexpr void segbitset<N>::__build(const std::bitset<N>& a, size_t l, size_t r, size_t x) noexcept {
  if (l == r) {
    SIZES[x] = 1;
    L[x] = l;
    tree[x] = a[l];
    return;
  }
  auto m = (l + r) >> 1;
  auto y = __ls(x), z = __rs(l, m, x);
  __build(a, l, m, y);
  __build(a, m + 1, r, z);
  __pushup(x, y, z);
}

template <size_t N>
constexpr segbitset<N>::segbitset(const std::bitset<N>& a) noexcept {
  __build(a, 0, N - 1, 0);
}

template <size_t N>
constexpr segbitset<N>::segbitset(const __segbitset& o) noexcept : tree(o.tree) {}

template <size_t N>
constexpr segbitset<N>& segbitset<N>::operator=(const __segbitset& o) noexcept {
  if (&o != this) tree = o.tree;
}

template <size_t N>
constexpr size_t segbitset<N>::__count(size_t l, size_t r, size_t x) const noexcept {
  if (!tree[x]) return 0;
  if (l == r) return 1;
  auto m = (l + r) >> 1;
  return __count(l, m, __ls(x)) + __count(m + 1, r, __rs(l, m, x));
}

template <size_t N>
constexpr size_t segbitset<N>::count() const noexcept {
  return __count(0, N - 1, 0);
}

template <size_t N>
constexpr size_t segbitset<N>::__find(size_t pos, size_t l, size_t r,
                                      size_t x) const noexcept {  // non-recusive
  while (l != r) {
    auto m = (l + r) >> 1;
    if (pos <= m) {
      x = __ls(x);
      r = m;
    } else {
      x = __rs(l, m, x);
      l = m + 1;
    }
  }
  return x;
}

template <size_t N>
constexpr bool segbitset<N>::test(size_t pos) const {
  if (pos >= N) throw std::out_of_range("segbitset::test pos >= N");
  return tree[__find(pos, 0, N - 1, 0)];
}

template <size_t N>
constexpr bool segbitset<N>::__all(size_t l, size_t r, size_t x) const noexcept {
  if (!tree[x]) return false;
  if (l == r) return tree[x];
  auto m = (l + r) >> 1;
  return __all(l, m, __ls(x)) && __all(m + 1, r, __rs(l, m, x));  // && has short circuit effect
}

template <size_t N>
constexpr bool segbitset<N>::all() const noexcept {
  return __all(0, N - 1, 0);
}

template <size_t N>
constexpr bool segbitset<N>::any() const noexcept {
  return tree[0];  // root == 1 indicates the whole tree contains true bits
}

template <size_t N>
constexpr bool segbitset<N>::none() const noexcept {
  return !tree[0];  // root == 0 indicates the whole tree contains no true bits
}

template <size_t N>
constexpr void segbitset<N>::__set(size_t pos, bool v, size_t l, size_t r, size_t x) noexcept {
  if (l == r) {
    tree[x] = v;
    return;
  }
  auto m = (l + r) >> 1;
  auto y = __ls(x), z = __rs(l, m, x);
  if (pos <= m)
    __set(pos, v, l, m, y);
  else
    __set(pos, v, m + 1, r, z);
  __pushup(x, y, z);
}

template <size_t N>
constexpr segbitset<N>& segbitset<N>::set() noexcept {
  tree.set();  // TODO: any faster solution?
  return *this;
}

template <size_t N>
constexpr segbitset<N>& segbitset<N>::set(size_t pos, bool value) {
  if (pos >= N) throw std::out_of_range("segbitset::set pos >= N");
  __set(pos, true, 0, N - 1, 0);
  return *this;
}

template <size_t N>
constexpr void segbitset<N>::__reset(size_t l, size_t r, size_t x) noexcept {
  if (!tree[x]) return;  // won't change
  if (l == r) {
    tree[x] = 0;
    return;
  }
  auto m = (l + r) >> 1;
  auto y = __ls(x), z = __rs(l, m, x);
  __reset(l, m, y);
  __reset(m + 1, r, z);
  __pushup(x, y, z);
}

template <size_t N>
constexpr segbitset<N>& segbitset<N>::reset() noexcept {
  // Not using tree.reset() (aka std::bitset's)
  // for hoping better performance on sparse dataset.
  // TODO: performance
  __reset(0, N - 1, 0);
  return *this;
}

template <size_t N>
constexpr segbitset<N>& segbitset<N>::reset(size_t pos) {
  if (pos >= N) throw std::out_of_range("segbitset::reset pos >= N");
  __set(pos, false, 0, N - 1, 0);
  return *this;
}

template <size_t N>
constexpr void segbitset<N>::__flip(size_t l, size_t r, size_t x) noexcept {
  if (l == r) {
    tree[x] = !tree[x];
    return;
  }
  auto m = (l + r) >> 1;
  auto y = __ls(x), z = __rs(l, m, x);
  __flip(l, m, y);
  __flip(m + 1, r, z);
  __pushup(x, y, z);
}

template <size_t N>
constexpr segbitset<N>& segbitset<N>::flip() noexcept {
  __flip(0, N - 1, 0);
  return *this;
}

template <size_t N>
constexpr bool segbitset<N>::__flip_pos(size_t pos, size_t l, size_t r, size_t x) noexcept {
  if (l == r) {
    tree[x] = !tree[x];
    return tree[x];
  }
  auto m = (l + r) >> 1;
  auto y = __ls(x), z = __rs(l, m, x);
  bool b;
  if (pos <= m)
    b = __flip_pos(pos, l, m, y);
  else
    b = __flip_pos(pos, m + 1, r, z);
  __pushup(x, y, z);
  return b;
}

template <size_t N>
constexpr segbitset<N>& segbitset<N>::flip(size_t pos) {
  if (pos >= N) throw std::out_of_range("segbitset::flip pos >= N");
  __flip_pos(pos, 0, N - 1, 0);
  return *this;
}

template <size_t N>
constexpr bool segbitset<N>::__equal(const segbitset<N>& rhs, size_t l, size_t r, size_t x) const noexcept {
  if (tree[x] != rhs.tree[x]) return false;
  if (!tree[x] && !rhs.tree[x]) return true;  // children of both are all 0.
  if (l == r) return true;
  auto m = (l + r) >> 1;
  return __equal(rhs, l, m, __ls(x)) && __equal(rhs, r, m + 1, __rs(l, m, x));
}

template <size_t N>
constexpr bool segbitset<N>::operator==(const segbitset<N>& rhs) const noexcept {
  return __equal(rhs, 0, N - 1, 0);
}

template <size_t N>
constexpr void segbitset<N>::__and_assign(const __segbitset& other, size_t l, size_t r, size_t x) noexcept {
  // 0 & 0 -> 0   *
  // 0 & 1 -> 0   *
  // 1 & 0 -> 0
  // 1 & 1 -> 1
  // if children of this tree are all zeros, results won't change.
  if (!tree[x]) return;
  if (l == r) {
    tree[x] = tree[x] & other.tree[x];
    return;
  }
  auto m = (l + r) >> 1;
  auto y = __ls(x), z = __rs(l, m, x);
  __and_assign(other, l, m, y);
  __and_assign(other, m + 1, r, z);
  __pushup(x, y, z);
}

template <size_t N>
constexpr segbitset<N>& segbitset<N>::operator&=(const segbitset<N>& other) noexcept {
  __and_assign(other, 0, N - 1, 0);
  return *this;
}

template <size_t N>
constexpr void segbitset<N>::__or_assign(const __segbitset& other, size_t l, size_t r, size_t x) noexcept {
  // 0 | 0 -> 0   *
  // 0 | 1 -> 1
  // 1 | 0 -> 1   *
  // 1 | 1 -> 1
  // if children of other are all of 0, results of this tree won't change.
  if (!other.tree[x]) return;
  if (l == r) {
    tree[x] = tree[x] | other.tree[x];
    return;
  }
  auto m = (l + r) >> 1;
  auto y = __ls(x), z = __rs(l, m, x);
  __or_assign(other, l, m, y);
  __or_assign(other, m + 1, r, z);
  __pushup(x, y, z);
}

template <size_t N>
constexpr segbitset<N>& segbitset<N>::operator|=(const segbitset<N>& other) noexcept {
  __or_assign(other, 0, N - 1, 0);
  return *this;
}

template <size_t N>
constexpr void segbitset<N>::__xor_assign(const __segbitset& other, size_t l, size_t r, size_t x) noexcept {
  // 0 ^ 0 -> 0    *
  // 0 ^ 1 -> 1
  // 1 ^ 0 -> 1    *
  // 1 ^ 1 -> 0
  // if children of other are all 0, tree won't change.
  if (!other.tree[x]) return;
  if (l == r) {
    tree[x] = tree[x] ^ other.tree[x];
    return;
  }
  auto m = (l + r) >> 1;
  auto y = __ls(x), z = __rs(l, m, x);
  __xor_assign(other, l, m, y);
  __xor_assign(other, m + 1, r, z);
  __pushup(x, y, z);
}

template <size_t N>
constexpr segbitset<N>& segbitset<N>::operator^=(const __segbitset& other) noexcept {
  __xor_assign(other, 0, N - 1, 0);
  return *this;
}

template <size_t N>
constexpr segbitset<N> segbitset<N>::operator~() const noexcept {
  auto clone = *this;
  clone.flip();  // inplace
  return clone;
}

template <size_t N>
constexpr void segbitset<N>::__to_bitset(std::bitset<N>& a, size_t l, size_t r, size_t x) noexcept {
  if (l == r) {
    a[l] = tree[x];
    return;
  }

  auto m = (l + r) >> 1;
  __to_bitset(a, l, m, __ls(x));
  __to_bitset(a, m + 1, r, __rs(l, m, x));
}

template <size_t N>
constexpr std::bitset<N> segbitset<N>::to_bitset() const noexcept {
  std::bitset<N> a;
  auto self = const_cast<__segbitset*>(this);
  self->__to_bitset(a, 0, N - 1, 0);
  return a;
}

template <size_t N>
constexpr void segbitset<N>::to_bitset(std::bitset<N>& a) noexcept {
  __to_bitset(a, 0, N - 1, 0);
}

template <size_t N>
constexpr void segbitset<N>::__next(size_t pos, size_t l, size_t r, size_t x, size_t& ans) const noexcept {
  if (!tree[x]) return;
  if (r < pos) return;  // skip previously scanned intervals.
  if (l == r) {
    ans = l;
    return;
  }
  auto m = (l + r) >> 1;
  auto y = __ls(x), z = __rs(l, m, x);
  if (ans == N && tree[y]) __next(pos, l, m, y, ans);
  if (ans == N && tree[z]) __next(pos, m + 1, r, z, ans);
}

template <size_t N>
constexpr size_t segbitset<N>::first() const noexcept {
  size_t ans = N;
  __next(0, 0, N - 1, 0, ans);
  return ans;
}

template <size_t N>
constexpr size_t segbitset<N>::next(size_t pos) const noexcept {
  ++pos;  // excludes previous result
  size_t ans = N;
  __next(pos, 0, N - 1, 0, ans);
  return ans;
}

template <size_t N>
constexpr void segbitset<N>::__foreach1(callback& cb, size_t l, size_t r, size_t x) const noexcept {
  if (!tree[x]) return;
  if (l == r) {
    cb(l);
    return;
  }
  auto m = (l + r) >> 1;
  auto y = __ls(x), z = __rs(l, m, x);
  if (tree[y]) __foreach1(cb, l, m, y);
  if (tree[z]) __foreach1(cb, m + 1, r, z);
}

template <size_t N>
constexpr void segbitset<N>::foreach1(callback& cb) const noexcept {
  // __foreach1(cb, 0, N - 1, 0);
  size_t x = 0;
  while (x < __N) {
    if (!tree[x]) {  // skip
      x += std::max(SIZES[x], (size_t)1);
      continue;
    }
    if (SIZES[x] == 1) cb(L[x]);
    x++;
  }
}

////////////////////////////////////////
/// reference
////////////////////////////////////////

template <size_t N>
constexpr typename segbitset<N>::reference segbitset<N>::operator[](size_t pos) {
  if (pos >= N) throw std::out_of_range("segbitset::operator[] pos >= N");
  auto x = __find(pos, 0, N - 1, 0);
  return segbitset<N>::reference(*this, x, pos);
}

template <size_t N>
constexpr typename segbitset<N>::reference& segbitset<N>::reference::operator=(bool value) noexcept {
  s.__set(pos, value, 0, N - 1, 0);
  return *this;
}

template <size_t N>
constexpr typename segbitset<N>::reference& segbitset<N>::reference::operator=(
    const segbitset<N>::reference& reference) noexcept {
  s.__set(pos, reference.s.tree[x], 0, N - 1, 0);
  return *this;
}

template <size_t N>
constexpr bool segbitset<N>::reference::operator~() const noexcept {
  return s.__flip_pos(pos, 0, N - 1, 0);
}

template <size_t N>
constexpr segbitset<N>::reference::operator bool() const noexcept {
  return s.tree[x];
}

template <size_t N>
constexpr typename segbitset<N>::reference& segbitset<N>::reference::flip() noexcept {
  s.__flip_pos(pos, 0, N - 1, 0);
  return *this;
}

////////////////////////////////////////
/// Non member operators
////////////////////////////////////////

template <size_t N>
constexpr segbitset<N> operator&(const segbitset<N>& lhs, const segbitset<N>& rhs) noexcept {
  auto s = lhs;
  s &= rhs;
  return s;
}

template <size_t N>
constexpr segbitset<N> operator|(const segbitset<N>& lhs, const segbitset<N>& rhs) noexcept {
  auto s = lhs;
  s |= rhs;
  return s;
}

template <size_t N>
constexpr segbitset<N> operator^(const segbitset<N>& lhs, const segbitset<N>& rhs) noexcept {
  auto s = lhs;
  s ^= rhs;
  return s;
}

}  // namespace segbitset

#endif
