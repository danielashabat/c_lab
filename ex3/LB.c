#include "buffer.h"
#include <stdio.h>
#include <string.h>

// Buffer is an abstraction to a char array that can handle any amount of chars to be written to

int main(int argc, char** argv)
{
    Buffer buff_ob;
    Buffer* buff = &buff_ob;
    buff->data = NULL;
    initialize_buffer(buff);

    char* str1 = "na \r\n\r\n kk";
    char* str2 = "olola\r\n\r\n";

    char* str3 = "AAA";
    char* str4 = "BBB\r\n\r\n";

    append_to_buffer(buff, str1, strlen(str1));
    print_buffer(buff);

    append_to_buffer(buff, str2, strlen(str2));
    print_buffer(buff);

    initialize_buffer(buff);

    append_to_buffer(buff, str3, strlen(str1));
    print_buffer(buff);

    append_to_buffer(buff, str4, strlen(str2));
    print_buffer(buff);

    printf("%d\n", buff->suffixes);
    free_buffer(buff);
}

//    winSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);