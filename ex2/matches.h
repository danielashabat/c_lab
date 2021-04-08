#ifndef MATCHES
#define MATCHES

#include <stdbool.h>

bool is_char_sequence_match(const char* p1, const char* p2, int len);
bool is_str_in_line(const char* line, const char* str);
bool is_str_match_line(const char* line, const char* str, bool i, bool x);

#endif