/*
 * bathroom.c
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron
 */

#include "bathroom.h"


void init(bathroom b){
	b.currentPeopleCount = 0;
	gettimeofday(&b.startTime, NULL);
	b.currentTime;
	b.state = Empty;
	b.totalPeopleCount = 0;
	b.time;
	b.longestWait = 0;
	b.shortestWait = -1;
	b.meanWait = 0;
	b.longestBath = 0;
	b.shortestBath = -1;
	b.meanBath = 0;
	printf("I am making the spinLock\n");
	if(pthread_spin_init(&b.lock, PTHREAD_PROCESS_SHARED)){
		printf("Bathroom Lock Creation Failed, Exiting Now");
		exit(-1);
	}
	pthread_spin_unlock(&b.lock);
	printf("I made the spin Lock\n");
}

void enter(gender g, bathroom b){
	while(b.state != g && b.state != Empty){pthread_yield();}
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
