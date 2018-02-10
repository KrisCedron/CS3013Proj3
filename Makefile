all: master

bathroom.o: bathroom.c bathroom.h
	gcc -c -g -pthread bathroom.c
	
master: master.c bathroom.o
	gcc -Wall -g  master.c bathroom.o -pthread -lm -o main
	
clean: 
	rm -f bathroom.o
	rm -f a.out