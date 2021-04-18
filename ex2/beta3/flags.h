

#ifndef FLAGS
#define FLAGS
#include <stdbool.h>

#define ARGS_ERROR 1
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
int extract_arguments(int argc, const char **argv, Flags *flags, char **search_word, char **file_name);
#endif