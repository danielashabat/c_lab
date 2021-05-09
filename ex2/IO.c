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
