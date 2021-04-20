//
// Created by Surface on 20/04/2021.
//
#include <stdio.h>
#include <stdlib.h>



void set_stream(const char* file_name, FILE** stream){
    if (file_name != NULL) {
        *stream = fopen(file_name, "r");
        if (*stream == NULL) {
            fprintf(stderr, "file not exist\n");
           exit(1);
        }
    } else {
        *stream = stdin;
    }

}
