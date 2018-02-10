/*
 * bathroom.h
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron
 */


#ifndef BATHROOM_H_
#define BATHROOM_H_
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum gender{Empty, Female, Male}gender;
typedef struct bathroom{
	pthread_spinlock_t lock;
	gender state;
	int currentPeopleCount;
	int totalPeopleCount;
	double startingTime;
	double currentTime;
}bathroom;

void enter(gender g, bathroom b);
void leave(bathroom b);
void init(bathroom b);

#endif /* BATHROOM_H_ */
