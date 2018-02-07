/*
 * bathroom.h
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron
 */

#ifndef BATHROOM_H_
#define BATHROOM_H_
typedef struct bathroom{
	int state;
	int currentPeopleCount;
	int totalPeopleCount;
	int currentTime;
}bathroom;
typedef enum gender{Empty, Female, Male}gender;

void enter(gender g, bathroom b);
void leave(void);

#endif /* BATHROOM_H_ */
