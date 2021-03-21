#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "IO.h"

#define DECIMAL_BASE 10

//internal funcions decleration
int myAtoi(char* str);

//functions definitions


int execute_command(Linked_List* list, char args[MAX_ARGS_NUM][MAX_LINE_LEN]) {
	int index;
	int elem;
	int elem_2;

	if (strings_equal(args[0], "add_end")) {
		elem = myAtoi(args[1]);
		add_to_end_of_list(elem, list);
	}

	else if (strings_equal(args[0], "add_start")) {
		elem = myAtoi(args[1]);
		add_to_start_of_list(elem, list);

	}

	else if (strings_equal(args[0], "add_after")) {
		elem = myAtoi(args[1]);
		elem_2 = myAtoi(args[2]);
		return add_after(elem, elem_2, list);
	}

	else if (strings_equal(args[0], "index")) {
		elem = myAtoi(args[1]);
		return print_index(elem, list);
	}
	else if (strings_equal(args[0], "del")) {
		index = myAtoi(args[1]);
		return delete_element_index_from_list(index, list);
	}

	else if (strings_equal(args[0], "print")) {
		print_list(list);
	}
	else if (strings_equal(args[0], "exit")) {
		terminate_list(list);
		exit(0);
	}
	else {
		printf("oops command not found\n");
	}

	return 0;
}



//credit to:
// https://www.geeksforgeeks.org/write-your-own-atoi/
int myAtoi(char* str)
{
	int res = 0;
	int i = 0;
	for (i = 0; str[i] != '\0'; ++i)
		res = res * DECIMAL_BASE + str[i] - '0';

	return res;
}


//this function reads a line (include spaces) from the user and adds in end of line '\0'
void get_row(char* input) {
	int i = -1;
	do {
		i++;
		scanf("%c", &input[i]);
	} 	while (input[i] != '\n');
	input[i] = '\0'; //replace '\n'  with '\0'
}


void extract_arguments_from_str(char* str, char args[MAX_ARGS_NUM][MAX_LINE_LEN]) {
	int arg_num = 0;
	int i = 0;
	int j = 0;

	while (str[i] != '\0') {
		if (str[i] == ' ') {
			args[arg_num][j] = '\0';
			arg_num++;//set to next argument
			i++;
			j = 0;
			continue;
		}

		args[arg_num][j] = str[i];
		i++;
		j++;
	}
	args[arg_num][j] = '\0';
}



int strings_equal(char* str1, char* str2) {
	int i = 0;

	while (str1[i] != '\0' || str2[i] != '\0') {
		if (str1[i] != str2[i]) {
			return 0;//strings not equal
		}
		i++;
	}

	return 1;//strings are equal

}





//credit to
// https://stackoverflow.com/questions/19300596/implementation-of-tolower-function-in-c
void ToLower(char* str)
{
	while (*str != '\0')
	{
		if (*str >= 'A' && *str <= 'Z')
		{
			*str = *str + 'a' - 'A';
		}
		str++;
	}

}
