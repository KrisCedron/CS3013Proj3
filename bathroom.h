/*
 * bathroom.h
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron and mrmcfatter
 */


#ifndef BATHROOM_H_
#define BATHROOM_H_
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef enum gender{Empty, Female, Male}gender;
typedef struct bathroom{
	pthread_spinlock_t lock;
	gender state;
	int currentPeopleCount;
	int totalPeopleCount;
	int lineCount;
	struct timeval startTime, currentTime, emptyStart, emptyEnd;
	double time;
	double emptyTime;
	//the necessary information for data collection
	double longestWait;
	double shortestWait;
	double meanWait;
	double longestBath;
	double shortestBath;
	double meanBath;
	int bathroomTrips;
	int incrementer;
	int linePeople;
	int bathroomPeople;

}bathroom;

void enter(gender g, bathroom b);
void leave(bathroom b);
void init(bathroom b);

#endif /* BATHROOM_H_ */
