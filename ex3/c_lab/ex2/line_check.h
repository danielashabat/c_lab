#ifndef LINE_CHECK
#define LINE_CHECK

#include "handle_arguments.h"
#include <stdbool.h>

typedef struct StrRange {
  char* str_top;
  char* str_bottom;
} StrRange;

bool is_word_match_line(const char* line, const char* str, const Flags* flags);

#endif
