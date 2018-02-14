all: master

bathroom.o: bathroom.c bathroom.h
	gcc -c -g -pthread bathroom.c
	
master: master.c bathroom.o
	gcc -Wall -g  master.c bathroom.o -pthread -lm -o bathroomSim
	
clean: 
	rm -f bathroom.o
	rm -f main