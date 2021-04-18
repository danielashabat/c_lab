my_grep: main.o import_data.o analyze_and_print.o flags.o matches.o
	gcc -o my_grep main.o flags.o import_data.o analyze_and_print.o matches.o

main.o:main.c  import_data.h analyze_and_print.h flags.h
	gcc -Wall -c main.c

import_data.o:import_data.c  import_data.h
	 gcc -Wall -c import_data.c

analyze_and_print.o:analyze_and_print.c  flags.h import_data.h analyze_and_print.h matches.h
	gcc -Wall -c analyze_and_print.c			

matches.o: matches.h flags.h matches.c
	gcc -Wall -c matches.c


flags.o: flags.h flags.c
	gcc -Wall -c flags.c

.PHONY: all clean test
clean:
	-rm *.o my_grep

all: my_grep
	
test: all
	~nimrodav/grep_tests/beta2.sh

