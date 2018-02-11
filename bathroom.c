/*
 * bathroom.c
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron
 */

#include "bathroom.h"


void init(bathroom b){
	b.currentPeopleCount = 0;
	b.startingTime = clock();
	b.currentTime;
	b.state = Empty;
	b.totalPeopleCount = 0;
	printf("I am making the spinLock\n");
	if(pthread_spin_init(&b.lock, PTHREAD_PROCESS_SHARED)){
		printf("Bathroom Lock Creation Failed, Exiting Now");
		exit(-1);
	}
	printf("I made the spin Lock\n");
}

void enter(gender g, bathroom b){
	printf("Please may i have a lock\n");
	pthread_spin_lock(&b.lock);
	printf("yes you may\n");
	b.currentPeopleCount++;
	if(b.currentPeopleCount == 1){
		b.state = g;
	}
	pthread_spin_unlock(&b.lock);
	printf("Have your lock back\n");
}
void leave(bathroom b){
	pthread_spin_lock(&b.lock);
	b.currentPeopleCount--;
	b.currentTime++;

	if(b.currentPeopleCount == 0){
		b.state = Empty;
	}
}
