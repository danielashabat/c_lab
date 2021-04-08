#include "analyze_and_print.h"
#include "matches.h"

void print_output(LinesData* lines_data)
{
    int i = 0;
    for (i = 0; i < lines_data->number_of_lines; i++) {
        if(lines_data->to_print[i])
        {
            printf("%s", lines_data->lines[i]);
        }
    }
}

void analyze_which_line_to_print(LinesData* lines_data, char* search_word)
{
    int i = 0;
    for (i = 0; i < lines_data->number_of_lines; i++) {
        if(number_of_str_matches_in_line(lines_data->lines[i],search_word)>0)
        {
            lines_data->to_print[i] = true;
        }
    }
}