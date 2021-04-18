out: main.o import_data.o analyze_and_print.o flags.o
	gcc -o out main.o flags.o import_data.o analyze_and_print.o matches.o

main.o: import_data.h analyze_and_print.h flags.h
	gcc -c main.c

import_data.o: import_data.h
	 gcc -c import_data.c

analyze_and_print.o: flags.h import_data.h analyze_and_print.h matches.h
			gcc -c analyze_and_print.c			

matches.o: matches.h flags.h
		gcc -c matches.c


flags.o: flags.h
	gcc -c flags.c

