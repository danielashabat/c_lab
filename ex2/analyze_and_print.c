#include "analyze_and_print.h"
#include "matches.h"

void print_output(LinesData* lines_data, Flags* flags)
{
    int i = 0;
    for (i = 0; i < lines_data->number_of_lines; i++) {
        if(lines_data->to_print[i])
        {
            printf("%s", lines_data->lines[i]);
        }
    }
}

void analyze_which_line_to_print(LinesData* lines_data, char* search_word, Flags* flags)
{
  int i = 0;
  for (i = 0; i < lines_data->number_of_lines; i++) {

      if(is_str_match_line(lines_data->lines[i],search_word,flags->i,flags->x))
      {
          lines_data->to_print[i] = true;
      }
  }
}