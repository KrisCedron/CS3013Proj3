/*
 * bathroom.h
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron
 */

#ifndef BATHROOM_H_
#define BATHROOM_H_
typedef enum gender{Empty, Female, Male}gender;
typedef struct bathroom{
	pthread_spinlock_t *lock;
	gender state;
	int currentPeopleCount;
	int totalPeopleCount;
	int currentTime;
}bathroom;

void enter(gender g, bathroom b);
void leave(void);
#endif /* BATHROOM_H_ */
