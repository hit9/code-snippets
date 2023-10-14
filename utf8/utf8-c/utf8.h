// Copyright (c) 2023, Chao Wang <hit9@icloud.com>
// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// utf8 encoding between codepoints.
// https://writings.sh/post/utf8

#ifndef HIT9_CODE_SNIPPETS_UTF8_H
#define HIT9_CODE_SNIPPETS_UTF8_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Count codepoints in given utf8 string.
size_t utf8_count(unsigned char* s, size_t slen);

// Decode utf8 string to codepoint buffer.
// Returns number of codepoints decoded.
// Returns 0 if given utf8 string is invalid.
size_t utf8_decode(unsigned char* s, size_t slen, uint32_t* p);

// Encode codepoint buffer to utf8 string.
// Returns number of chars encoded.
// Returns 0 if given codepoint buffer is invalid.
size_t utf8_encode(uint32_t* p, size_t plen, unsigned char* s);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // HIT9_CODE_SNIPPETS_UTF8_H
