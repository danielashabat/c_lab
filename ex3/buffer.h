#ifndef BUFFER
#define BUFFER
typedef struct Buffer {
  char* data;
  int chars_allocated;
  int chars_count;
  int suffixes;
} Buffer;

void initialize_buffer(Buffer* buff);
void free_buffer(Buffer* buff);
void append_to_buffer(Buffer* buff, char* text, int chars_to_write);
void print_buffer(Buffer* buff);
#endif
