// Copyright 2023 hit9
// https://writings.sh/post/utf8

#ifndef HIT9_CODE_SNIPPETS_UTF8_H
#define HIT9_CODE_SNIPPETS_UTF8_H

#include <cstddef>
#include <string>
#include <string_view>

namespace utf8 {

using size_t = std::size_t;

// Count codepoints in given utf8 string.
size_t Count(std::string_view s);

// Decode utf8 string to codepoint buffer.
// Returns number of codepoints decoded.
// Returns 0 if given utf8 string is invalid.
size_t Decode(std::string_view s, std::u32string& p);

// Encode codepoint buffer to utf8 string.
// Returns number of chars encoded.
// Returns 0 if given codepoint buffer is invalid.
size_t Encode(std::u32string_view, std::string& s);

}  // namespace utf8
#endif  // HIT9_CODE_SNIPPETS_UTF8_H
