
#include "analyze_and_print.h"
#include "flags.h"
#include "import_data.h"
#include <stdio.h>
#include <stdlib.h>

#define MIN_ARGC 3

int main(int argc, char* argv[])
{
  FILE* stream = NULL;
  char** lines = NULL;
  int number_of_lines = 0;
  LinesData* lines_data = NULL;
  char* search_word = NULL;
  Flags flags_obj;
  Flags* flags = &flags_obj;

  int file_index = argc - 1;
  int search_word_index = argc - 2;
  int ret_val = 0;

  if (argc < MIN_ARGC) {
    fprintf(stderr, "not enough arguments\n");
    return 1;
  }

  stream = fopen(argv[file_index], "r");
  if (stream == NULL) {
    fprintf(stderr, "file not exist\n");
    return 1;
  }
  search_word = (char*)malloc(sizeof(char) * (strlen(argv[search_word_index]) + 1));
  if (search_word == NULL) {
    printf("ERROR: malloc() failed\n");
    return 1;
  }
  strcpy(search_word, argv[search_word_index]);
  initialize_flags(flags);
  if (argc > MIN_ARGC) {
    ret_val = set_flags_from_user(flags, argc, argv);
    if (ret_val == ARGS_ERROR) {
      return ARGS_ERROR;
    }
  }

  import_stream_to_lines_arr(stream, &lines, &number_of_lines);
  lines_data = create_lines_data(lines, number_of_lines);
  analyze_which_line_to_print(lines_data, search_word, flags);
  print_output(lines_data, flags);
  free_lines_data(lines_data);
  free(search_word);
  return 0;
}
