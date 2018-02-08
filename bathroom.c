/*
 * bathroom.c
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron
 */

#include "bathroom.h"

void enter(gender g, bathroom b){
	while(g == b.state || b.state == Empty){} //spinLock
	//test_and_set();
}
void leave(bathroom b){
	b.currentPeopleCount--;
	b.currentTime++;
}
