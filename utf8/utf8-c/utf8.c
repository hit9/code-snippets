#include "utf8.h"

// https://writings.sh/post/utf8

// Code copy from http://bjoern.hoehrmann.de/utf-8/decoder/dfa.
// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

// clang-format off

#define UTF8_ACCEPT 0
#define UTF8_REJECT 1

static const unsigned char utf8d[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 00..1f // NOLINT
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 20..3f // NOLINT
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 40..5f // NOLINT
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 60..7f // NOLINT
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9, // 80..9f // NOLINT
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, // a0..bf // NOLINT
  8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, // c0..df // NOLINT
  0xa,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x4,0x3,0x3, // e0..ef // NOLINT
  0xb,0x6,0x6,0x6,0x5,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8, // f0..ff // NOLINT
  0x0,0x1,0x2,0x3,0x5,0x8,0x7,0x1,0x1,0x1,0x4,0x6,0x1,0x1,0x1,0x1, // s0..s0 // NOLINT
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1, // s1..s2 // NOLINT
  1,2,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1, // s3..s4 // NOLINT
  1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,1,1,1,1,1,1, // s5..s6 // NOLINT
  1,3,1,1,1,1,1,3,1,3,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // s7..s8 // NOLINT
};

static uint32_t inline
utf8_decode_next(uint32_t* state, uint32_t* codep, unsigned char byte) {
  uint32_t type = utf8d[byte];

  *codep = (*state != UTF8_ACCEPT) ?
    (byte & 0x3fu) | (*codep << 6) :
    (0xff >> type) & (byte);

  *state = utf8d[256 + *state*16 + type];
  return *state;
}

// clang-format on
// Code copy end.

size_t utf8_count(unsigned char* s, size_t slen) {
    unsigned char* end = s + slen;
    size_t k = 0;

    while (s != end) {
        if ((*s & 0xc0) != 0x80) k++;  // count non-continuation bytes.
        s++;
    }
    return k;
}

size_t utf8_decode(unsigned char* s, size_t slen, uint32_t* p) {
    unsigned char* end = s + slen;
    uint32_t state = 0;
    uint32_t codep;
    size_t k = 0;

    while (s != end) {
        if (!utf8_decode_next(&state, &codep, *s)) p[k++] = codep;
        s++;
    }
    if (state != UTF8_ACCEPT) return 0;
    return k;
}

static size_t utf8_encode_code(uint32_t code, unsigned char* s) {
    if (code <= 0x7f) {
        s[0] = code;
        return 1;
    }
    if (code <= 0x7ff) {
        s[0] = 0xc0 | (code >> 6);    // 110xxxxx
        s[1] = 0x80 | (code & 0x3f);  // 10xxxxxx
        return 2;
    }
    if (code <= 0xffff) {
        s[0] = 0xe0 | (code >> 12);          // 1110xxxx
        s[1] = 0x80 | ((code >> 6) & 0x3f);  // 10xxxxxx
        s[2] = 0x80 | (code & 0x3f);         // 10xxxxxx
        return 3;
    }
    if (code <= 0x10ffff) {
        s[0] = 0xf0 | (code >> 18);           // 11110xxx
        s[1] = 0x80 | ((code >> 12) & 0x3f);  // 10xxxxxx
        s[2] = 0x80 | ((code >> 6) & 0x3f);   // 10xxxxxx
        s[3] = 0x80 | (code & 0x3f);          // 10xxxxxx
        return 4;
    }
    return 0;
}

size_t utf8_encode(uint32_t* p, size_t plen, unsigned char* s) {
    size_t k = 0;
    size_t j = 0;
    while (k != plen) {
        size_t d = utf8_encode_code(p[k++], s);
        if (!d) return 0;
        s += d;
        j += d;
    }
    return j;
}
