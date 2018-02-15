/*
 * bathroom.c
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron and mrmcfatter
 */

#include "bathroom.h"


void init(bathroom* b){
	b->currentPeopleCount = 0;
	gettimeofday(&b->startTime, NULL);
	gettimeofday(&b->currentTime, NULL);
	gettimeofday(&b->emptyStart, NULL);
	gettimeofday(&b->emptyEnd, NULL);
	b->emptyTime = 0;
	b->state = Empty;
	b->totalPeopleCount = 0;
	b->time = 0;
	b->longestWait = 0;
	b->shortestWait = -1;
	b->meanWait = 0;
	b->longestBath = 0;
	b->shortestBath = -1;
	b->meanBath = 0;
	b->bathroomTrips = 0;
	b->incrementer = 0;
	b->linePeople = 0;
	b->bathroomPeople = 0;
	b->lineCount = 0;
	//printf("I am making the spinLock\n");
	if(pthread_spin_init(&b->lock, PTHREAD_PROCESS_SHARED)){
		printf("Bathroom Lock Creation Failed, Exiting Now");
		exit(-1);
	}
	//printf("I made the spin Lock\n");
}

void enter(gender g, bathroom* b){
	while(b->state != g && b->state != Empty){
		//printf("I can't Enter the Bathrrom, my Gender is %d and the bathroom is occupied by: %d\n", g, b->state);
		pthread_yield();
	}
	//printf("Please may i have a lock\n");
	b->lineCount++;
	pthread_spin_lock(&b->lock);
	b->lineCount--;
	b->bathroomTrips++;
	//printf("yes you may\n");
	b->currentPeopleCount++;
	//printf("Current People Count: %d\n", b->currentPeopleCount);
	if(b->currentPeopleCount == 1){
		b->state = g;
		gettimeofday(&b->emptyEnd, NULL);
		b->emptyTime = b->emptyTime + (b->emptyEnd.tv_sec - b->emptyStart.tv_sec) + ((b->emptyEnd.tv_usec - b->emptyStart.tv_usec)/1000000.0);
	}
	assert(b->state == g);
	pthread_spin_unlock(&b->lock);
	//printf("IM IN BITECHES\n");
}
void leave(bathroom* b){
	pthread_spin_lock(&b->lock);
	b->currentPeopleCount--;
	if(b->currentPeopleCount == 0){
		b->state = Empty;
		gettimeofday(&b->emptyStart, NULL);
	}
	pthread_spin_unlock(&b->lock);
	//printf("IM OUT BITECHES\n");
}
