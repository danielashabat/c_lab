#ifndef MATCHES
#define MATCHES

#include "flags.h"
#include <stdbool.h>



bool is_str_match_line(const char* line, const char* str, Flags* flags);

#endif