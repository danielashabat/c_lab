
#ifndef FLAGS
#define FLAGS
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

void initialize_flags(Flags* flags);

#endif
