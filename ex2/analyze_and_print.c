#include "analyze_and_print.h"
#include "line_check.h"

void flip_matches(LinesData* lines_data);
int number_of_matches(const LinesData* lines_data);
void analyze_extra_lines_to_print(LinesData* lines_data, const Flags* flags);
void print_line(int i, const LinesData* lines_data, char splitter, const Flags* flags);
void print_separation_sign_if_needed(int i, const LinesData* lines_data);
bool is_last_print(int i, const LinesData* lines_data);

void print_output(const LinesData* lines_data, const Flags* flags)
{
  char splitter;
  int i;
  if (flags->c) {
    printf("%d\n", number_of_matches(lines_data));
  } else {
    for (i = 0; i < lines_data->number_of_lines; i++) {
      if (lines_data->to_print[i]) {
        splitter = ':';
        print_line(i, lines_data, splitter, flags);
      }
      if (lines_data->to_extra_print[i]) {
        splitter = '-';
        print_line(i, lines_data, splitter, flags);
        print_separation_sign_if_needed(i, lines_data);
      }
    }
  }
}
void print_separation_sign_if_needed(int i, const LinesData* lines_data)
{
  if (lines_data->line_numbers[i] == lines_data->number_of_lines) {
    return;
  }
  if ((lines_data->to_print[i + 1]) || (lines_data->to_extra_print[i + 1])) {
    return;
  }
  if (is_last_print(i, lines_data)) {
    return;
  }
  printf("--\n");
}

bool is_last_print(int i, const LinesData* lines_data)
{
  int j;
  for (j = i + 1; j < lines_data->number_of_lines; j++) {
    if ((lines_data->to_print[j]) || (lines_data->to_extra_print[j])) {
      return false;
    }
  }
  return true;
}

void print_line(int i, const LinesData* lines_data, char splitter, const Flags* flags)
{
  if (flags->n) {
    printf("%d%c", lines_data->line_numbers[i], splitter);
  }
  if (flags->b) {
    printf("%d%c", lines_data->byte_offsets[i], splitter);
  }
  printf("%s\n", lines_data->lines[i]);
}
int number_of_matches(const LinesData* lines_data)
{
  int i;
  int num = 0;
  for (i = 0; i < lines_data->number_of_lines; i++) {
    if (lines_data->to_print[i]) {
      num++;
    }
  }
  return num;
}

void analyze_which_line_to_print(LinesData* lines_data, const char* search_word, const Flags* flags)
{
  int i = 0;
  for (i = 0; i < lines_data->number_of_lines; i++) {
    lines_data->to_print[i] = is_word_match_line((const char*)lines_data->lines[i], search_word, flags);
  }
  if (flags->v) {
    flip_matches(lines_data);
  }
  if (flags->A) {
    analyze_extra_lines_to_print(lines_data, flags);
  }
}
void analyze_extra_lines_to_print(LinesData* lines_data, const Flags* flags)
{
  int i;
  int counter = 0;
  for (i = 0; i < lines_data->number_of_lines; i++) {
    if (lines_data->to_print[i]) {
      counter = flags->NUM;
    } else {
      if (counter > 0) {
        lines_data->to_extra_print[i] = true;
        counter--;
      }
    }
  }
}
void flip_matches(LinesData* lines_data)
{
  int i;
  for (i = 0; i < lines_data->number_of_lines; i++) {
    lines_data->to_print[i] = !(lines_data->to_print[i]);
  }
}
