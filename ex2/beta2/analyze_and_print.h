#ifndef ANALYZE_AND_PRINT
#define ANALYZE_AND_PRINT

#include "flags.h"
#include "import_data.h"

void print_output(const LinesData* lines_data, const Flags* flags);
void analyze_which_line_to_print(LinesData* lines_data, char* search_word, const Flags* flags);
#endif  // ANALYZE_AND_PRINT
