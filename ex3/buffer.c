
#include "buffer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BASIC_BUFF_LEN 100
#define SUFFIX_LENGTH 4

void update_number_of_suffixes(Buffer* buff);
bool is_char_sequence_match(char* word1, char* word2, int len);

void initialize_buffer(Buffer* buff)
{
  if (buff->data != NULL) {
    free(buff->data);
  }
  buff->data = (char*)malloc((BASIC_BUFF_LEN) * sizeof(char));
  if (buff->data == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(1);
  }
  buff->chars_count = 0;
  buff->chars_allocated = BASIC_BUFF_LEN;
  buff->suffixes = 0;
}

void free_buffer(Buffer* buff) { free(buff->data); }

void append_to_buffer(Buffer* buff, char* text, int chars_to_write)
{
  int i;
try_to_write:
  if (buff->chars_count + chars_to_write <= buff->chars_allocated) {
    // append to buffer
    for (i = 0; i < chars_to_write; i++) {
      buff->data[buff->chars_count + i] = text[i];
    }
    buff->chars_count = buff->chars_count + chars_to_write;
  } else {
    buff->data = (char*)realloc(buff->data, 2 * (buff->chars_allocated));
    if (buff->data == NULL) {
      fprintf(stderr, "realloc() failed\n");
      exit(1);
    }
    buff->chars_allocated = 2 * (buff->chars_allocated);
    goto try_to_write;
  }
  update_number_of_suffixes(buff);
}

void print_buffer(Buffer* buff)
{
  int i;
  for (i = 0; i < buff->chars_count; i++) {
    printf("%c", buff->data[i]);
  }
  printf("\n");
}

void update_number_of_suffixes(Buffer* buff)
{
  char* suffix = "\r\n\r\n";
  int i;
  if (buff->chars_count < SUFFIX_LENGTH) {
    return;
  }
  buff->suffixes = 0;
  for (i = 0; i < buff->chars_count - SUFFIX_LENGTH + 1; i++) {
    if (is_char_sequence_match(buff->data + (sizeof(char)) * i, suffix, SUFFIX_LENGTH)) {
      buff->suffixes++;
    }
  }
}

bool is_char_sequence_match(char* word1, char* word2, int len)
{
  int i = 0;
  for (i = 0; i < len; i++) {
    if (word1[i] != word2[i]) {
      return false;
    }
  }
  return true;
}