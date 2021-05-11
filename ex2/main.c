
#include "IO.h"
#include "analyze_and_print.h"
#include "lines_data.h"
#include "matches.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN_ARGC 2

int main(int argc, char** argv)
{
  FILE* stream = NULL;
  char** lines = NULL;
  int number_of_lines = 0;
  LinesData* lines_data = NULL;
  Flags flags_obj;
  Flags* flags = &flags_obj;

  const char* search_word = NULL;
  const char* file_name = NULL;

  if (argc < MIN_ARGC) {
    fprintf(stderr, "not enough arguments\n");
    return 1;
  }
  initialize_flags(flags);
  extract_arguments(argc, (const char**)argv, flags, &search_word, &file_name);
  set_stream(file_name, &stream);

  import_stream_to_lines_arr(stream, &lines, &number_of_lines);
  lines_data = create_lines_data(lines, number_of_lines);
  analyze_which_line_to_print(lines_data, search_word, flags);
  print_output(lines_data, flags);
  free_lines_data(lines_data);

  if (stream != stdin) {
    fclose(stream);
  }
  return 0;
}
