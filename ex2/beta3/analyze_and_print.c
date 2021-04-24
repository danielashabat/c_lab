#include <string.h>
#include <stdlib.h>
#include "analyze_and_print.h"
#include "matches.h"

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

void analyze_which_line_to_print(LinesData* lines_data, char* search_word, const Flags* flags)
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



//return the first occurence of char in word, if no occurence found return -1;
int get_index_of_char(const char* word,const char c){
    int i=0;
    for(i=0; i<strlen(word);i++){
        if (word[i]== c) {
            if ((i > 0 && word[i-1] == '\\') ){
                continue;
            }
            return i;
        }
    }
    return -1;
}

void split_search_word_to_2_branches(char *search_word,char** search_word1,char** search_word2){
    int char_index=0;
    int search_word_index=0;
    int search_word1_index=0;
    int search_word2_index=0;

    *search_word1= (char*)malloc((strlen(search_word)+1)*sizeof(char));
    *search_word2= (char*)malloc((strlen(search_word)+1)*sizeof(char));
    if (*search_word1 == NULL || *search_word2 == NULL){
        fprintf(stderr, "malloc() failed \n");
        exit(1);
    }
    char* ptr_search_word1=*search_word1;
    char* ptr_search_word2=*search_word2;
    char_index = get_index_of_char(search_word, '(');
    if (char_index == -1){
        strncpy( ptr_search_word1,search_word,strlen(search_word));
        strncpy( ptr_search_word2,search_word,strlen(search_word));
        return;
    }


    for(search_word_index=0; search_word_index < char_index ; search_word_index++){
        ptr_search_word1[search_word1_index]=search_word[search_word_index];
        ptr_search_word2[search_word2_index]=search_word[search_word_index];
        search_word1_index++;
        search_word2_index++;
    }
    char_index = get_index_of_char(search_word, '|');

    for(search_word_index=search_word_index+1; search_word_index < char_index ; search_word_index++){
        ptr_search_word1[search_word1_index]=search_word[search_word_index];
        search_word1_index++;
    }


    char_index = get_index_of_char(search_word, ')');
    for(search_word_index= search_word_index + 1; search_word_index < char_index ; search_word_index++){
        ptr_search_word2[search_word2_index]=search_word[search_word_index];
        search_word2_index++;
    }

    for(search_word_index= search_word_index + 1; search_word_index <= strlen(search_word) ; search_word_index++){
        ptr_search_word1[search_word1_index]=search_word[search_word_index];
        ptr_search_word2[search_word2_index]=search_word[search_word_index];
        search_word1_index++;
        search_word2_index++;
    }


}
