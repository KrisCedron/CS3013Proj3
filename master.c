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

bathroom b;


void thread(){
	int gender = 1; //a boolean, 1 indicates that it is a man, 0 indicates that it is a woman
	double meanArrival = .25; //the mean arrival time
	double stddevArrival = meanArrival/2;
	double meanStay = .50; //the average time that people stay
	double stddevStay = meanStay/2;
	int loopCount = 3;//the number of times the person is meant to go to the bathroom
	int loopCounter = 1;
	int currentStatus = 0;//indicates whether they are or are not in the bathroom
	//HERE IS ALSO WHERE THE PARAMETERS ARE TO BE ADDED FOR STATISICS

	double arrivalTime = sqrt(-2 * log(meanArrival)) * cos(2 * 3.14 * stddevArrival);
	double bathroomTime;

	while(loopCounter <= loopCount){
		if(arrivalTime <= b.currentTime){
			printf("Hey my name is Jimmy and I have to go to the bathroom!!\n");
			enter();
			printf("Hey my name is Jimmy and I'm in the bathroom!\n");
			bathroomTime = (sqrt(-2 * log(meanStay)) * cos(2 * 3.14 * stddevStay)) + b.currentTime;
			b.currentTime++;
		}//if
		else if(bathroomTime <= b.currentTime){
			printf("Hey my name is Jimmy, and I'm done using the bathroom!\n");
			leave();
			printf("Hey my name is Jimmy and I just left the bathroom after using it for the %d time!\n", loopCounter);
			arrivalTime = (sqrt(-2 * log(meanStay)) * cos(2 * 3.14 * stddevStay)) + b.currentTime;
			printf("My name be Jimmy and I'm gonna need to pee again at %f\n", arrivalTime);
			loopCounter = 1;
			b.currentTime++;
		}//else if
		else{
			b.currentTime++;
		}
		if(loopCounter == loopCount){
			printf("Hey my name is Jimmy and I don't need to go to the bathroom anymore!");
		}//if
	}//while
}//thread()




int main(void){
	//create 1 pthread for the example

	pthread_t *jimmy;

	pthread_create(jimmy, NULL, *thread(), NULL);


}//main
