my_grep: main.o import_data.o analyze_and_print.o handle_arguments.o line_check.o
	gcc -o my_grep main.o  import_data.o analyze_and_print.o handle_arguments.o line_check.o

main.o: main.c import_data.h analyze_and_print.h handle_arguments.h
	gcc -Wall -c main.c

handle_arguments.o: handle_arguments.h handle_arguments.c 
	 gcc -Wall -c handle_arguments.c

line_check.o: line_check.c  line_check.h handle_arguments.h 
	gcc -Wall -c line_check.c
	

import_data.o:import_data.c  import_data.h
		 gcc -Wall -c import_data.c

analyze_and_print.o:analyze_and_print.c  import_data.h analyze_and_print.h handle_arguments.h line_check.h
		gcc -Wall -c analyze_and_print.c			


.PHONY: all clean test
clean:
	-rm *.o my_grep

all: my_grep

test: all
	~nimrodav/grep_tests/run_all.sh
	~danielas1/git/ex2/my_tests.sh
