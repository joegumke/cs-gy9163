default: prog

get-deps:
	# Assuming Debian or Ubuntu here
	sudo apt-get install -y build-essential check

dictionary.o: dictionary.c
	gcc -Wall -c dictionary.c dictionary.h

spell.o: spell.c
	gcc -Wall -c spell.c

test.o: test_main.c
	gcc -Wall -c test_main.c

main.o: main.c
	gcc -Wall -c main.c

test: dictionary.o spell.o test_main.o
	#gcc -Wall -o test_main test_main.o spell.o dictionary.o -lcheck -lm -lrt -lpthread -lsubunit
	gcc -o test_main dictionary.c dictionary.h spell.c test_main.c -Wall -lcheck -lm -lrt -lpthread -lsubunit
	./test_main 

prog: dictionary.o spell.o main.o
	#gcc -Wall -o spell_check dictionary.o spell.o main.o
	gcc -o main dictionary.c dictionary.h spell.c main.c -Wall -lcheck -lm -lrt -lpthread -lsubunit
	./main test1.txt wordlist.txt

clean:
	rm dictionary.o spell.o main.o test_main main dictionary.h.gch

cleanall:clean
	rm spell_check
	
