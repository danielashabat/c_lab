
#include "analyze_and_print.h"
#include "flags.h"
#include "import_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGC_NUM 3

int main(int argc, char* argv[])
{
  FILE* stream = NULL;
  char** lines = NULL;
  int number_of_lines = 0;
  LinesData* lines_data = NULL;
  char* search_word = NULL;
  Flags flags_obj;
  Flags* flags = &flags_obj;

  search_word = (char*)malloc(sizeof(char) * (strlen(argv[1]) + 1));
  if (search_word == NULL) {
    printf("ERROR: malloc() failed\n");
    return 1;
  }
  strcpy(search_word, argv[1]);
  initialize_flags(flags);

  if (argc == ARGC_NUM) {
    stream = fopen(argv[2], "r");
    if (stream == NULL) {
      fprintf(stderr, "file not exist\n");
      return 1;
    }
  } else {
    printf("ERROR: missing or extra argumenets, please insert 'grep <reg> <file>'\n");
    return 1;
  }
  import_stream_to_lines_arr(stream, &lines, &number_of_lines);
  lines_data = create_lines_data(lines, number_of_lines);

  analyze_which_line_to_print(lines_data, search_word, flags);
  print_output(lines_data, flags);
  free_lines_data(lines_data);
  free(search_word);
  return 0;
}
