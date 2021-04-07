
#include <string.h>
#include "matches.h"

bool is_char_sequence_match(const char* p1, const char* p2, int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        if (*(p1 + i) != *(p2 + i))
        {
            return false;
        }
    }
    return true;
}

int number_of_str_matches_in_line(const char* line, const char* str)
{
    int num = 0;
    int i = 0;
    if (strlen(line) < strlen(str)) {
        return 0;
    }
    for (i = 0; i <= strlen(line) - strlen(str); i++)
    {
        if (is_char_sequence_match(line + i, str, strlen(str)))
        {
            num++;
        }
    }
    return num;
}