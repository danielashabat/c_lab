
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

void initialize_flags(Flags* flags);
int set_flags_from_user(Flags* flags, int argc,const char* argv[]);
#endif
