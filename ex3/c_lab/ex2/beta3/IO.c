#include <stdlib.h>
#include "IO.h"



void set_stream(const char* file_name, FILE** stream)
{
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

int extract_arguments(int argc, const char** argv, Flags* flags, const char** search_word, const char** file_name)
{
    int i = 1;

    for (i = 1; i < argc; i++) {

        if (is_flag(argv[i])) {
            set_flag(flags, argv, &i);
        } else {
            if (*search_word == NULL) {
                *search_word = argv[i];
            } else {
                *file_name = argv[i];
            }
        }
    }
    return 0;
}