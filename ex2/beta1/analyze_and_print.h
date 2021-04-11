#ifndef ANALYZE_AND_PRINT
#define ANALYZE_AND_PRINT

#include "flags.h"
#include "import_data.h"

void print_output(LinesData* lines_data, Flags* flags);
void analyze_which_line_to_print(LinesData* lines_data, char* search_word, Flags* flags);
#endif  // ANALYZE_AND_PRINT
