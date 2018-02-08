/* Christian Cedron and Marc McFatter
 * CS 3013
 * Project 3
 * Operating Systems C 2018
 *
 * master.c
 *
 * This is the code where the threads will be created and then run, where the information will be stored,
 * and then outputted.
 */

#include <math.h>
#include <pthread.h>
#include "bathroom.h"


void thread(){
	int gender = 1; //a boolean, 1 indicates that it is a man, 0 indicates that it is a woman
	double meanArrival = .25; //the mean arrival time
	double stddevArrival = meanArrival/2;
	double meanStay = .50; //the average time that people stay
	double stddevStay = meanStay/2;
	int loopCount = 3;//the number of times the person is meant to go to the bathroom
	int currentStatus = 0;//indicates whether they are or are not in the bathroom
	//HERE IS ALSO WHERE THE PARAMETERS ARE TO BE ADDED FOR STATISICS

	double arrivalTime = sqrt(-2 * log(meanArrival)) * cos(2 * 3.14 * stddevArrival);
	double bathrromTime = sqrt(-2 * log(meanStay)) * cos(2 * 3.14 * stddevStay);

	int time = 0;

	while(1){
		if(arrivalTime <= time){
			printf("Hey my name is Jimmy and I have to go to the bathroom!!\n")
			enter();

			leave();

		}//if
	}//while
}//thread()

int time = 0;


int main(void){
	//create 1 pthread for the example
	int time = 0;

	pthread_create();

	int x = 0;
	while(x);
	x++;
	if(jimmy.loopCount )
}
