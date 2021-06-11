#include <stdio.h>
#include "linked_list.h"
#include "IO.h"


int main(){
	char input[MAX_LINE_LEN] ;
	char args[MAX_ARGS_NUM][MAX_LINE_LEN] ;
	int ret_val=0;
	Linked_List* list = create_emplty_Linked_List();

	while (1){
		get_row(input);
		ToLower(input);
		extract_arguments_from_str(input, args);
   		ret_val =execute_command(list, args);
		if (ret_val !=0){
			if (ret_val ==ERROR_INVALID_VALUE){
				printf("ERROR: invalid value \n");
				return ERROR_INVALID_VALUE;
				}

                        if (ret_val ==ERROR_INVALID_INDEX){
                                printf("ERROR: invalid index\n");
				return ERROR_INVALID_INDEX ;
			}
		}
	}
return 0;
}

