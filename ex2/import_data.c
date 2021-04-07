
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "import_data.h"
/*functions declarations*/





void free_lines_arr(char** lines, int number_of_lines) {
    int i = 0;
    for (i = 0; i < number_of_lines; i++) {
        free(lines[i]);
    }
}

//lines and number_of_lines are uninitialized vars
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

        printf("read from stream:%s\n", array[i]);
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
