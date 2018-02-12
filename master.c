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
	int threadNumber;
}inputStruct;


void *thread(void *voidIn){
	inputStruct *structIn = voidIn;
	int gender = structIn->genIn;
	double meanArrival = structIn->arrivalIn; //the mean arrival time
	double stddevArrival = meanArrival/2;
	double meanStay = structIn->stayIn; //the average time that people stay
	double stddevStay = meanStay/2;
	int loopCount = structIn->loopsIn;//the number of times the person is meant to go to the bathroom
	int number = structIn->threadNumber;
	int currState = NotPeeing;

	//HERE IS ALSO WHERE THE PARAMETERS ARE TO BE ADDED FOR STATISICS
	double waitAvg = 0;
	double waitMin = 10000000000;
	double waitMax = 0;
	double bathAvg = 0;
	double bathMin = 10000000000;
	double bathMax = 0;

	double arrivalTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevArrival) + meanArrival + b.currentTime;
	double bathroomTime;
	init(b);

	printf("First Pee Time: %f\n",arrivalTime);
	while(loopCount > 0){
		if(currState == NotPeeing && arrivalTime <= b.currentTime){
			printf("Hey my name is %d and I have to go to the bathroom!!\n", number);
			enter(gender, b);
			currState = Peeing;
			printf("Hey my name is %d and I'm in the bathroom!\n", number);
			bathroomTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevStay) + meanStay  + b.currentTime;
			printf("My name be %d and I'm gonna pee until %f\n", number, bathroomTime);
		}//if
		else if(currState == Peeing && bathroomTime <= b.currentTime){
			printf("Hey my name is %d, and I'm done using the bathroom!\n", number);
			leave(b);
			currState = NotPeeing;
			arrivalTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevArrival) + meanArrival + b.currentTime;
			printf("My name be %d and I'm gonna need to pee again at %f\n", number, arrivalTime);
			loopCount--;
		}//else if
		else{
			printf("Im %d And I dont Need to Pee\n", number);
		}
		printf("%f\n", b.currentTime);
	}//while
	printf("Hey my name is %d and I don't need to go to the bathroom anymore!", number);
	return NULL;
}//thread()


void makeNewThread(int gender, double meanArrival, double meanStay, int loopCount, int number, pthread_t* threadID){
	inputStruct* newThreadVals = (inputStruct*)malloc(sizeof(inputStruct));

	newThreadVals->genIn = gender;
	newThreadVals->arrivalIn = meanArrival;
	newThreadVals->stayIn = meanStay;
	newThreadVals->loopsIn = loopCount;
	newThreadVals->threadNumber = number;

	pthread_create(threadID, NULL, thread, newThreadVals);
	free(newThreadVals);
}

int main(void){
	int threadCount = 25;
	pthread_t* threadIDs = (pthread_t*)calloc(sizeof(pthread_t), threadCount);

	double meanArrival = 10;
	double meanStay = 5;

	for(int i = 0; i < threadCount; i++){
		makeNewThread((i%2)+1, meanArrival, meanStay, 1000, i , &threadIDs[i]);
	}

	pthread_join(threadIDs[1], NULL);
	pthread_join(threadIDs[0], NULL);

	return 0;
}//main
