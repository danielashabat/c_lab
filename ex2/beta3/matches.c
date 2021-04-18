
#include "matches.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_RANGE_EXP_LENGTH 5 //  [a|b] -> 5 chars

void ToLower(char* str);
bool is_char_range_sequence_match(const char* line, const char* str_top, const char* str_bottom, int len);
bool is_str_range_in_line(const char* line, const char* str_top, const char* str_bottom);
StrRange* create_str_range(int size);
void free_str_range(StrRange* str_range);
StrRange* interpret_regular_expression(const char* search_word);
bool is_char_range_sequence_match(const char* line, const char* str_top, const char* str_bottom, int len)
{
  int i = 0;
  for (i = 0; i < len; i++) {
    if (*(line + i) > *(str_top + i) || *(line + i) < *(str_bottom + i)) {
      return false;
    }
  }
  return true;
}

bool is_str_range_in_line(const char* line, const char* str_top, const char* str_bottom)
{

  int i = 0;
  if (strlen(line) < strlen(str_top)) {
    return false;
  }
  for (i = 0; i <= strlen(line) - strlen(str_top); i++) {
    if (is_char_range_sequence_match(line + i, str_top, str_bottom, strlen(str_top))) {
      return true;
    }
  }
  return false;
}

// credit to
// https://stackoverflow.com/questions/19300596/implementation-of-tolower-function-in-c
void ToLower(char* str)
{
  while (*str != '\0') {
    if (*str >= 'A' && *str <= 'Z') {
      *str = *str + 'a' - 'A';
    }
    str++;
  }
}

bool is_word_match_line(const char* line, const char* word, Flags* flags)
{
    StrRange* str_range = NULL;
    bool ret_val;
    char* line_m = NULL;
    char* word_m = NULL;
    line_m = (char*)malloc((strlen(line) + 1) * sizeof(char));
    word_m = (char*)malloc((strlen(word) + 1) * sizeof(char));
    if (line_m == NULL || word_m == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(1);
    }

    strcpy(line_m, line);
    strcpy(word_m, word);

    if (flags->i) {
        ToLower(line_m);
        ToLower(word_m);
    }
    if(flags->E)
    {
        str_range = interpret_regular_expression(word_m);
        ret_val = is_str_range_in_line(line_m, str_range->str_top, str_range->str_bottom);
        if (flags->x)
        {
            ret_val = ret_val && (strlen(line_m) == strlen(str_range->str_top));
        }
        free_str_range(str_range);
    }
    else
    {
        ret_val = is_str_range_in_line(line_m, word_m, word_m);
        if (flags->x)
        {
            ret_val = ret_val && (strlen(line_m) == strlen(word_m));
        }
    }


    free(line_m);
    free(word_m);
    return ret_val;
}

StrRange* create_str_range(int size)
{
    char* str_top = NULL;
    char* str_bottom = NULL;
    StrRange* str_range = NULL;

    str_top = (char*)malloc((size+1) * sizeof(char));
    str_bottom = (char*)malloc((size+1) * sizeof(char));
    str_range = (StrRange*)malloc(sizeof(StrRange));

    if(str_top == NULL || str_bottom == NULL || str_range == NULL )
    {
        fprintf(stderr, "malloc() failed\n");
        exit(1);
    }
    str_range->str_top = str_top;
    str_range->str_bottom = str_bottom;
    return str_range;
}

void free_str_range(StrRange* str_range)
{
    free(str_range->str_top);
    free(str_range->str_bottom);
    free(str_range);
}

StrRange* interpret_regular_expression(const char* search_word)
{
    int size = strlen(search_word);
    StrRange* str_range = create_str_range(size);
    int i;
    int place = 0;
    for(i=0;i<size;i++)
    {
        switch(search_word[i])
        {
            case '\\':
                str_range->str_top[place] = search_word[i+1];
                str_range->str_bottom[place] = search_word[i+1];
                i++;
                break;
            case '.':
                str_range->str_top[place] = '~';
                str_range->str_bottom[place] = '!';
                break;
            case '[':
                str_range->str_top[place] = search_word[i+3];
                str_range->str_bottom[place] = search_word[i+1];
                i=i+CHAR_RANGE_EXP_LENGTH-1;
                break;
            default:
                str_range->str_top[place] = search_word[i];
                str_range->str_bottom[place] = search_word[i];
        }
        place++;
    }
    str_range->str_top[place] = '\0';
    str_range->str_bottom[place] = '\0';

//    printf("search: %s\n",search_word);
//    printf("top: %s\n",str_range->str_top);
//    printf("bottom: %s\n",str_range->str_bottom);
    return str_range;
}