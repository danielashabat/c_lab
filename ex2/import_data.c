
#include <string.h>
#include <stdlib.h>

#include "import_data.h"


void free_lines_arr(char** lines, int number_of_lines) {
    int i = 0;
    for (i = 0; i < number_of_lines; i++) {
        free(lines[i]);
    }
}

int import_stream_to_lines_arr(FILE* stream, char*** lines, int* number_of_lines) {
    size_t size = 10;
    int status = 0;
    int i = 0;
    char** array = NULL;


    array = (char**)malloc(sizeof(char*));

    while (true) {
        array[i] = NULL;
        status = getline(&array[i], &size, stream);
        if (status == EOF) {
            //free extra line
            free(array[i]);
            break;
        }

        i++;
        array = (char**)realloc(array, sizeof(char*) * (i + 1));
        if (array == NULL) {
            fprintf(stderr, "realloc() failed\n");
            return 1;
        }
    }

    *lines = array;
    *number_of_lines = i;
    return 0;
}

LinesData* create_lines_data(char** lines, int number_of_lines)
{
    int i=0;
    int offset=0;
    LinesData* lines_data = NULL;
    int* line_numbers = NULL;
    int* byte_offsets = NULL;
    bool* to_print = NULL;

    lines_data = (LinesData*)malloc(sizeof(LinesData));
    line_numbers = (int*)malloc(number_of_lines*sizeof(int));
    byte_offsets = (int*)malloc(number_of_lines*sizeof(int));
    to_print = (int*)malloc(number_of_lines*sizeof(bool));
    if (lines_data == NULL || line_numbers == NULL || byte_offsets == NULL || to_print == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(1);
    }
    for(i=0;i<number_of_lines;i++)
    {
        line_numbers[i] = i + 1;
        byte_offsets[i] = offset;
        to_print[i] = false;
        offset = offset + strlen(lines[i]);
    }
    lines_data->lines = lines;
    lines_data->line_numbers = line_numbers;
    lines_data->byte_offsets = byte_offsets;
    lines_data->number_of_lines = number_of_lines;
    lines_data->to_print = to_print;
    return lines_data;
}

void free_lines_data(LinesData* lines_data)
{
    free_lines_arr(lines_data->lines,lines_data->number_of_lines);
    free(lines_data->line_numbers);
    free(lines_data->byte_offsets);
    free(lines_data->to_print);
    free(lines_data);
}

