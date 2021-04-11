
#include "analyze_and_print.h"
#include "flags.h"
#include "import_data.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  FILE* stream = NULL;
  char** lines = NULL;
  int i;
  int number_of_lines = 0;
  LinesData* lines_data = NULL;
  char* search_word = NULL;
  Flags flags_obj;
  Flags* flags = &flags_obj;

  initialize_flags(flags);

  /*this section need to be in main function*/
  if (argc == 3) {
    stream = fopen(argv[2], "r");
    if (stream == NULL) {
      fprintf(stderr, "file not exist\n");
      return 1;
    }
  } else {
    stream = stdin;
  }
  //**********************************
  //    search_word = argv[1];
  flags->i = true;
  //    flags->x=true;
  flags->n = true;
  flags->b = true;
  flags->v = true;
  //    flags->c=true;
  flags->NUM = 2;
  //    flags->A=true;
  search_word = "kkk";
  import_stream_to_lines_arr(stream, &lines, &number_of_lines);
  lines_data = create_lines_data(lines, number_of_lines);

  // DEBUG
  //    printf("number of lines is: %d\n", number_of_lines);
  analyze_which_line_to_print(lines_data, search_word, flags);
  print_output(lines_data, flags);
  free_lines_data(lines_data);
  return 0;
}
