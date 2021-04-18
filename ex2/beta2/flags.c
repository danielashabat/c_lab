#include "flags.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void  set_flag(Flags* flags, const char **argv, int* index );
int is_flag(const char* argument);


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

int extract_arguments(int argc, const char **argv, Flags *flags, char **search_word, char **file_name)
{
  int i = 1;

  for (i = 1; i < argc; i++) {

      if (is_flag(argv[i])) {
          set_flag(flags,argv, &i);
      }
      else {
          if (*search_word == NULL) {
              *search_word = argv[i];
          }
          else {
              *file_name = argv[i];
          }
      }
  }
  return 0;
}
int is_flag(const char* argument){
    if (argument[0] == '-') {
        return 1;
    }
    return 0;
}


void  set_flag(Flags* flags, const char **argv, int* index )
{

    char* flag = argv[*index];
  switch (flag[1])  {
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
      *index= *index+1;
      break;
    case 'E':
      flags->E = true;
      break;
    default:
      printf("ERROR: '%s' this is not a valid flag\n", flag);
  }

}
