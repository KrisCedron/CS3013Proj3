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
enum state{NotPeeing, Peeing};
typedef struct inputStruct{
	int genIn;
	double arrivalIn;
	double stayIn;
	int loopsIn;
	char* name;
}inputStruct;


void *thread(void *voidIn){
	inputStruct *structIn = voidIn;
	int gender = structIn->genIn;
	double meanArrival = structIn->arrivalIn; //the mean arrival time
	double stddevArrival = meanArrival/2;
	double meanStay = structIn->stayIn; //the average time that people stay
	double stddevStay = meanStay/2;
	int loopCount = structIn->loopsIn;//the number of times the person is meant to go to the bathroom
	int currState = NotPeeing;
	char* name = structIn->name;

//	int currentStatus = 0;//indicates whether they are or are not in the bathroom
	//HERE IS ALSO WHERE THE PARAMETERS ARE TO BE ADDED FOR STATISICS

	double arrivalTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevArrival) + meanArrival + b.currentTime;
	double bathroomTime;
	init(b);
	printf("%d\n", pthread_spin_unlock(&b.lock));
	printf("First Pee Time: %f\n",arrivalTime);
	while(loopCount > 0){
		if(currState == NotPeeing && arrivalTime <= b.currentTime){
			printf("Hey my name is %s and I have to go to the bathroom!!\n", name);
			enter(gender, b);
			currState = Peeing;
			printf("Hey my name is %s and I'm in the bathroom!\n", name);
			bathroomTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevStay) + meanStay  + b.currentTime;
			printf("My name be %s and I'm gonna pee until %f\n", name, bathroomTime);
		}//if
		else if(currState == Peeing && bathroomTime <= b.currentTime){
			printf("Hey my name is %s, and I'm done using the bathroom!\n", name);
			leave(b);
			currState = NotPeeing;
			arrivalTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevArrival) + meanArrival + b.currentTime;
			printf("My name be %s and I'm gonna need to pee again at %f\n", name, arrivalTime);
			loopCount--;
		}//else if
		else{
			printf("Im %s And I dont Need to Pee\n", name);
		}
		printf("Current Time Is: %d\n---------------------------------\n", b.currentTime);
		b.currentTime++;
	}//while
	printf("Hey my name is %s and I don't need to go to the bathroom anymore!", name);
	return NULL;
}//thread()




int main(void){
	int threadCount = 2;
	//create 1 pthread for the example
	pthread_t jimmy;
	pthread_t joanne;

	inputStruct* threadInfo = calloc(threadCount, sizeof(inputStruct));
	threadInfo[0].arrivalIn = 10;
	threadInfo[0].genIn = Male;
	threadInfo[0].loopsIn = 10000;
	threadInfo[0].stayIn = 5;
	threadInfo[0].name = "Jimmy";

	threadInfo[1].arrivalIn = 20;
	threadInfo[1].genIn = Female;
	threadInfo[1].loopsIn = 10000;
	threadInfo[1].stayIn = 10;
	threadInfo[1].name = "Joanne";

	pthread_create(&jimmy, NULL, thread, &threadInfo[0]);
	pthread_create(&joanne, NULL, thread, &threadInfo[1]);

	pthread_join(jimmy, NULL);
	pthread_join(joanne, NULL);

	return 0;
}//main
