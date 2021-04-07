
#include <stdio.h>
#include "matches.h"
#include "import_data.h"
//#include <stdlib.h>





int main(int argc, char* argv[]) {
    FILE* stream = NULL;
    char** lines = NULL;
    int i = 0;
    int number_of_lines = 0;


    /*this section need to be in main function*/
    if (argc == 2) {
        stream = fopen(argv[1], "r");
        if (stream == NULL) {
            fprintf(stderr, "file not exist\n");
            return 1;
        }
    }
    else {
        stream = stdin;
    }
    /**********************************/

    import_stream_to_lines_arr(stream, &lines, &number_of_lines);
    //DEBUG
    printf("number of lines is: %d\n", number_of_lines);
    for (i = 0; i < number_of_lines; i++) {
        printf("line %d: %s", i + 1, lines[i]);
    }

    free_lines_arr(lines, number_of_lines);
    return 0;
}

//char* str = "jjj";
//char* line = "AAAA123jjjjjjjjjjjkkkzzz";
//int num = number_of_str_matches_in_line(line, str);
//
//if (num > 0)
//{
//	printf("match, %d\n", num);
//}
//else
//{
//	printf("no\n");
//}