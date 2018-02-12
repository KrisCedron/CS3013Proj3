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
#include <sys/time.h>
#include "bathroom.h"

bathroom b;
enum state {
	NotPeeing, Peeing
};
typedef struct inputStruct {
	int genIn;
	double arrivalIn;
	double stayIn;
	int loopsIn;
	char* name;
} inputStruct;

void *thread(void *voidIn) {
	inputStruct *structIn = voidIn;
	int gender = structIn->genIn;
	double meanArrival = structIn->arrivalIn; //the mean arrival time
	double stddevArrival = meanArrival / 2;
	double meanStay = structIn->stayIn; //the average time that people stay
	double stddevStay = meanStay / 2;
	int loopCount = structIn->loopsIn; //the number of times the person is meant to go to the bathroom
	int numLoops = loopCount;
	int currState = NotPeeing;
	char* name = structIn->name;

	//HERE IS ALSO WHERE THE PARAMETERS ARE TO BE ADDED FOR STATISICS
	double waitAvg = 0;
	double waitMin;
	double waitMax = 0;
	double bathAvg = 0;
	double bathMin;
	double bathMax = 0;
	//we need the actual clock to get the time itself
	struct timeval waitStartTime, waitFinTime, bathStartTime, bathFinTime;
	double opTime;

	double arrivalTime =
			((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48()))
					* stddevArrival) + meanArrival + b.currentTime;
	double bathroomTime;
	init(b);
	printf("%d\n", pthread_spin_unlock(&b.lock));
	printf("First Pee Time: %f\n", arrivalTime);
	while (loopCount > 0) {
		if (currState == NotPeeing && arrivalTime <= b.time) {
			printf("Hey my name is %s and I have to go to the bathroom!!\n",
					name);
			gettimeofday(&waitStartTime, NULL);
			enter(gender, b);
			gettimeofday(&waitFinTime, NULL);
			opTime = waitStartTime.tv_usec - waitFinTime.tv_usec;
			waitAvg = waitAvg + opTime; //for computing the average wait time
			if (loopCount == numLoops) { //if this is the person's first time going to the bathroom for the sake of calculating min
				waitMin = opTime;
				if (b.shortestWait < 0) { //since we initialize the shortest wait as -1, this is the "first input" case
					b.shortestWait = opTime;
				}
			}
			if (opTime < waitMin) {
				waitMin = opTime;
				if (opTime < b.shortestWait) {
					b.shortestWait = opTime;
				}
			}
			if (opTime > waitMax) {
				waitMax = opTime;
				if (opTime > b.longestWait) {
					b.longestWait = opTime;
				}
			}
			currState = Peeing;
			printf("Hey my name is %s and I'm in the bathroom!\n", name);
			bathroomTime = ((sqrt(-2 * log(drand48()))
					* cos(2 * 3.14 * drand48())) * stddevStay) + meanStay
					+ b.currentTime;
			printf("My name be %s and I'm gonna pee until %f\n", name,
					bathroomTime);
		} //if
		else if (currState == Peeing && bathroomTime <= b.time) {
			printf("Hey my name is %s, and I'm done using the bathroom!\n",
					name);
			gettimeofday(&bathStartTime, NULL);
			leave(b);
			gettimeofday(&bathFinTime, NULL);
			opTime = bathStartTime.tv_usec - bathFinTime.tv_usec;
			waitAvg = bathAvg + opTime; //for computing the average wait time
			if (loopCount == numLoops) { //if this is the person's first time going to the bathroom for the sake of calculating min
				bathMin = opTime;
				if (b.shortestBath < 0) { //since we initialize the shortest wait as -1, this is the "first input" case
					b.shortestBath = opTime;
				}
			}
			if (opTime < bathMin) {
				bathMin = opTime;
				if (opTime < b.shortestBath) {
					b.shortestBath = opTime;
				}
			}
			if (opTime > bathMax) {
				bathMax = opTime;
				if (opTime > b.longestBath) {
					b.longestBath = opTime;
				}
			}
			currState = NotPeeing;
			arrivalTime = ((sqrt(-2 * log(drand48()))
					* cos(2 * 3.14 * drand48())) * stddevArrival) + meanArrival
					+ b.currentTime;
			printf("My name be %s and I'm gonna need to pee again at %f\n",
					name, arrivalTime);
			loopCount--;
		} //else if
		else {
			printf("Im %s And I dont Need to Pee\n", name);
		}
		//to keep the time updated, after anyone goes through an operation, we check the time.
		gettimeofday(&b.currentTime, NULL);
		b.time = (b.currentTime.tv_usec - b.startTime.tv_usec);
	} //while
	printf("Hey my name is %s and I don't need to go to the bathroom anymore!",
			name);
	return NULL;
} //thread()

int main(void) {
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
} //main
