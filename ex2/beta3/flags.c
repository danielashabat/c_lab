
#include <string.h>
#include "flags.h"

int set_single_flag(Flags* flags,const char* flag);

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

int set_flags_from_user(Flags* flags, int argc,const char* argv[]) {
    int i=1;
    int total_flags=argc-2;
    int ret_val=0;
    for (i=1; i<total_flags; i++){
        ret_val=set_single_flag(flags,argv[i]);
        if (ret_val== 'A' ){
            flags->NUM = atoi(argv[i+1]);
            i++;
        }
        else if (ret_val==  ARGS_ERROR){
            return ARGS_ERROR;
        }
    }
}

int set_single_flag(Flags* flags,const char* flag){
    if (flag[0] != '-'){
        printf("ERROR: '%s' this is not a flag\n",flag);
        return ARGS_ERROR;
    }
    switch(flag[1]){
        case 'i':
            flags->i=true;
            break;
        case 'v':
            flags->v=true;
            break;
        case 'c':
            flags->c=true;
            break;
        case 'n':
            flags->n=true;
            break;
        case 'b':
            flags->b=true;
            break;
        case 'x':
            flags->x=true;
            break;
        case 'A':
            flags->A=true;
            break;
        case 'E':
            flags->E=true;
            break;
        default:
            printf("ERROR: '%s' this is not a valid flag\n",flag);
            return ARGS_ERROR;

    }
    return flag[1];
}
