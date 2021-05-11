#ifndef HANDLE_ARGUMENTS
#define HANDLE_ARGUMENTS
#include <stdbool.h>

typedef struct Flags {
  bool i;
  bool v;
  bool c;
  bool n;
  bool b;
  bool x;
  bool A;
  int NUM;
  bool E;
} Flags;

void initialize_flags(Flags *flags);
void set_flag(Flags* flags, const char** argv, int* index);
int is_flag(const char* argument);
int extract_arguments(int argc, const char **argv, Flags *flags, const char **search_word, const char **file_name);

#endif
