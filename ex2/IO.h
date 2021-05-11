#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "flags.h"

void set_stream(const char* file_name, FILE** stream);
int extract_arguments(int argc, const char **argv, Flags *flags, const char **search_word, const char **file_name);
#endif
