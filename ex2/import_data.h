#ifndef IMPORT_DATA
#define IMPORT_DATA
#include <stdbool.h>
#include <stdio.h>

typedef struct LinesData {
    int number_of_lines;
    char** lines;
    int* line_numbers;
    int* byte_offsets;
    bool* to_print;
    bool* to_extra_print;
} LinesData;

void free_lines_arr(char** lines, const int number_of_lines);
int import_stream_to_lines_arr(FILE* stream, char*** lines, int* number_of_lines);
LinesData* create_lines_data(char** lines, int number_of_lines);
void free_lines_data(LinesData* lines_data);
#endif
