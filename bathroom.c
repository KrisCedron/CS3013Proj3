/*
 * bathroom.c
 *
 *  Created on: Feb 7, 2018
 *      Author: ccedron
 */

#include "bathroom.h"

void enter(gender g, bathroom b){
	while(g != b.state || b.state != Empty){}//spinLock

}
void leave(void){

}
