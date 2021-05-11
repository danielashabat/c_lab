#include "analyze_and_print.h"
#include "matches.h"
#include <stdlib.h>
#include <string.h>

void flip_matches(LinesData* lines_data);
int number_of_matches(const LinesData* lines_data);
void analyze_extra_lines_to_print(LinesData* lines_data, const Flags* flags);
void print_line(int i, const LinesData* lines_data, char splitter, const Flags* flags);
void print_separation_sign_if_needed(int i, const LinesData* lines_data);
bool is_last_print(int i, const LinesData* lines_data);
int copy_string_until_delimiter(char* dest_str, const char* src_str, char delim);


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

// return the first occurence of char in word, if no occurence found return -1;
int get_index_of_char(const char* word, const char c)
{
  int i = 0;
  for (i = 0; i < strlen(word); i++) {
    if ((i == 0) && word[i] == c) {
      return i;
    } else if ((word[i] == c) && (word[i - 1] != '\\')) {
      return i;
    }
  }
  return -1;
}

void split_search_word_to_2_branches(const char* search_word, char** search_word1, char** search_word2)
{
  int num_of_copied_chars = 0;
  char* ptr_search_word1 = NULL;
  char* ptr_search_word2 = NULL;

  *search_word1 = (char*)malloc((strlen(search_word) + 1) * sizeof(char));
  *search_word2 = (char*)malloc((strlen(search_word) + 1) * sizeof(char));
  if (*search_word1 == NULL || *search_word2 == NULL) {
    fprintf(stderr, "malloc() failed \n");
    exit(1);
  }
  ptr_search_word1 = *search_word1;
  ptr_search_word2 = *search_word2;

  // copy chars from search_word until the first '('
  num_of_copied_chars = copy_string_until_delimiter(ptr_search_word1, search_word, '(');
  ptr_search_word1 += num_of_copied_chars;
  copy_string_until_delimiter(ptr_search_word2, search_word, '(');
  ptr_search_word2 += num_of_copied_chars;
  search_word += num_of_copied_chars + 1;

  // copy the first or string
  num_of_copied_chars = copy_string_until_delimiter(ptr_search_word1, search_word, '|');
  search_word += num_of_copied_chars + 1;
  ptr_search_word1 += num_of_copied_chars;

  // copy the second or string
  num_of_copied_chars = copy_string_until_delimiter(ptr_search_word2, search_word, ')');
  ptr_search_word2 += num_of_copied_chars;
  search_word += num_of_copied_chars + 1;

  // copy the rest of chars in search_word include null terminate
  strncpy(ptr_search_word1, search_word, strlen(search_word) + 1);
  strncpy(ptr_search_word2, search_word, strlen(search_word) + 1);
  return;
}

int copy_string_until_delimiter(char* dest_str, const char* src_str, char delim)
{
  int char_index = 0;
  char_index = get_index_of_char(src_str, delim);
  if (char_index == -1) {
    fprintf(stderr, "ERROR: search word is invalid\n");
    exit(1);
  }
  strncpy(dest_str, src_str, char_index);
  return char_index;
}
