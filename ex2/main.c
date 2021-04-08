
#include <stdio.h>
#include <stdlib.h>
#include "import_data.h"
#include "analyze_and_print.h"


int main(int argc, char* argv[]) {
    FILE* stream = NULL;
    char** lines = NULL;
    int i = 0;
    int number_of_lines = 0;
    LinesData* lines_data = NULL;
    char* search_word = NULL;


    /*this section need to be in main function*/
    if (argc == 3) {
        stream = fopen(argv[2], "r");
        if (stream == NULL) {
            fprintf(stderr, "file not exist\n");
            return 1;
        }
    }
    else {
        stream = stdin;
    }
    //**********************************
//    search_word = argv[1];
    search_word = "pink";
    import_stream_to_lines_arr(stream, &lines, &number_of_lines);
    lines_data = create_lines_data(lines, number_of_lines);


    //DEBUG
//    printf("number of lines is: %d\n", number_of_lines);
    analyze_which_line_to_print(lines_data, search_word);
    print_output(lines_data);
    free_lines_data(lines_data);
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