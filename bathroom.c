/*
 * bathroom.c
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron
 */

#include "bathroom.h"

void enter(gender g, bathroom b){
	//test_and_set() spinLock
	b.currentPeopleCount--;
	b.currentTime++;

}
void leave(bathroom b){
	b.currentPeopleCount--;
	b.currentTime++;
}
