/*
 * bathroom.c
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron
 */

#include "bathroom.h"
#include <pthread.h>
#include <stdio.h>

void init(bathroom b){
	b.currentPeopleCount = 0;
	b.currentTime = 0;
	b.state = Empty;
	b.totalPeopleCount = 0;
	if(pthread_spin_init(b.lock, PTHREAD_PROCESS_SHARED)){
		printf("Bathroom Lock Creation Failed, Exiting Now");
		exit(-1);
	}
}

void enter(gender g, bathroom b){
	pthread_spin_lock(b.lock);
	b.currentPeopleCount--;
	b.currentTime++;
	if(b.currentPeopleCount == 1){
		b.state = g;
	pthread_spin_unlock(b.lock);
}
void leave(bathroom b){
	pthread_spin_lock(b.lock);
	b.currentPeopleCount--;
	b.currentTime++;

	if(b.currentPeopleCount == 0){
		b.state = Empty;
	}
	pthread_spin_unlock(b.lock);
}
