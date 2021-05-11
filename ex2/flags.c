
#include "flags.h"
#include <stdio.h>
#include <stdlib.h>


void initialize_flags(Flags* flags)
{
  flags->i = false;
  flags->v = false;
  flags->c = false;
  flags->n = false;
  flags->b = false;
  flags->x = false;
  flags->A = false;
  flags->NUM = 0;
  flags->E = false;
}


int is_flag(const char* argument)
{
  if (argument[0] == '-') {
    return 1;
  }
  return 0;
}

void set_flag(Flags* flags, const char** argv, int* index)
{

  const char* flag = argv[*index];
  switch (flag[1]) {
    case 'i':
      flags->i = true;
      break;
    case 'v':
      flags->v = true;
      break;
    case 'c':
      flags->c = true;
      break;
    case 'n':
      flags->n = true;
      break;
    case 'b':
      flags->b = true;
      break;
    case 'x':
      flags->x = true;
      break;
    case 'A':
      flags->A = true;
      flags->NUM = atoi(argv[*index + 1]);
      *index = *index + 1;
      break;
    case 'E':
      flags->E = true;
      break;
    default:
      printf("ERROR: '%s' this is not a valid flag\n", flag);
  }
}
