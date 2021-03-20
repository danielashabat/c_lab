#ifndef IO
#define IO


#include "linked_list.h"

#define MAX_ARGS_NUM  3
#define MAX_LINE_LEN 100
void get_row(char *input);
void ToLower(char *str);
int strings_equal(char *str1, char *str2);
void extract_arguments_from_str(char *str,char args[MAX_ARGS_NUM][MAX_LINE_LEN]) ;
int execute_command(Linked_List* list,char args[MAX_ARGS_NUM][MAX_LINE_LEN]);





#endif
