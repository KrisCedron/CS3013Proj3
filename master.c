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
#include <unistd.h>
#include <pthread.h>
#include "bathroom.h"

bathroom b;


void *thread(){
	int gender = Male;
	double meanArrival = .25; //the mean arrival time
	double stddevArrival = meanArrival/2;
	double meanStay = .50; //the average time that people stay
	double stddevStay = meanStay/2;
	int loopCount = 3;//the number of times the person is meant to go to the bathroom
	int loopCounter = 1;
//	int currentStatus = 0;//indicates whether they are or are not in the bathroom
	//HERE IS ALSO WHERE THE PARAMETERS ARE TO BE ADDED FOR STATISICS

	double arrivalTime = (sqrt(-2 * log(meanArrival)) * abs((int)cos(2 * 3.14 * stddevArrival))) + b.currentTime;
	double bathroomTime;
	init(b);

	while(loopCounter <= loopCount){
		if(arrivalTime <= b.currentTime){
			printf("Hey my name is Jimmy and I have to go to the bathroom!!\n");
			enter(gender, b);
			printf("Hey my name is Jimmy and I'm in the bathroom!\n");
			bathroomTime = (sqrt(-2 * log(meanStay)) * abs((int)cos(2 * 3.14 * stddevStay))) + b.currentTime;
			b.currentTime++;
		}//if
		else if(bathroomTime <= b.currentTime){
			printf("Hey my name is Jimmy, and I'm done using the bathroom!\n");
			leave(b);
			printf("Hey my name is Jimmy and I just left the bathroom after using it for the %d time!\n", loopCounter);
			arrivalTime = (sqrt(-2 * log(meanArrival)) * abs((int)cos(2 * 3.14 * stddevArrival))) + b.currentTime;
			printf("My name be Jimmy and I'm gonna need to pee again at %f\n", arrivalTime);
			loopCounter = 1;
			b.currentTime++;
		}//else if
		else{
			b.currentTime++;
			printf("\"I dont need to pee\"\n-Jimmy\n");
		}
		if(loopCounter == loopCount){
			printf("Hey my name is Jimmy and I don't need to go to the bathroom anymore!");
		}//if
	}//while
	return NULL;
}//thread()




int main(void){
	//create 1 pthread for the example
	pthread_t jimmy;
	pthread_create(&jimmy, NULL, thread, NULL);
	pthread_join(jimmy, NULL);
	return 0;
}//main
