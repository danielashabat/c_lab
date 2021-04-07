#ifndef IMPORT_DATA
#define IMPORT_DATA

#include <stdio.h>

void free_lines_arr(char** lines, const int number_of_lines);
int import_stream_to_lines_arr(FILE* stream, char*** lines, int* number_of_lines);

#endif
