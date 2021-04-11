
#include "matches.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ToLower(char* str);

bool is_char_sequence_match(const char* p1, const char* p2, int len)
{
  int i = 0;
  for (i = 0; i < len; i++) {
    if (*(p1 + i) != *(p2 + i)) {
      return false;
    }
  }
  return true;
}

bool is_str_in_line(const char* line, const char* str)
{

  int i = 0;
  if (strlen(line) < strlen(str)) {
    return false;
  }
  for (i = 0; i <= strlen(line) - strlen(str); i++) {
    if (is_char_sequence_match(line + i, str, strlen(str))) {
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

bool is_str_match_line(const char* line, const char* str, Flags* flags)
{
  bool ret_val;
  char* line_m = NULL;
  char* str_m = NULL;
  line_m = (char*)malloc((strlen(line) + 1) * sizeof(char));
  str_m = (char*)malloc((strlen(str) + 1) * sizeof(char));
  if (line_m == NULL || str_m == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(1);
  }

  strcpy(line_m, line);
  strcpy(str_m, str);

  if (flags->i) {
    ToLower(line_m);
    ToLower(str_m);
  }

  if (flags->x) {
    ret_val = (strcmp(line_m, str_m) == 0);
  } else {
    ret_val = is_str_in_line(line_m, str_m);
  }

  free(line_m);
  free(str_m);
  return ret_val;
}
