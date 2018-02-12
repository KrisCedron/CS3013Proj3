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
#include <time.h>
#include "bathroom.h"

bathroom b;
enum state{NotPeeing, Peeing};

void *thread(){
	int gender = Male;
	double meanArrival = 5; //the mean arrival time
	double stddevArrival = meanArrival/2;
	double meanStay = 10; //the average time that people stay
	double stddevStay = meanStay/2;
	int loopCount = 50;//the number of times the person is meant to go to the bathroom
	int averageCounter = loopCount;
	int currState = NotPeeing;
	//HERE IS ALSO WHERE THE PARAMETERS ARE TO BE ADDED FOR STATISICS
	double waitAvg = 0;
	double waitMin = -1;
	double waitMax = 0;
	double bathAvg = 0;
	double bathMin = -1;
	double bathMax = 0;
	//we need the actual clock to get the time itself
	clock_t waitStartTime;
	clock_t waitFinTime;
	clock_t bathStartTime;
	clock_t bathFinTime;
	double opTime;

	double arrivalTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevArrival) + meanArrival + b.currentTime;
	double bathroomTime;
	init(b);
	printf("%d\n", pthread_spin_unlock(&b.lock));
	printf("First Pee Time: %f\n",arrivalTime);
	while(b.currentTime <= loopCount){
		if(currState == NotPeeing && arrivalTime <= b.currentTime){
			printf("Hey my name is Jimmy and I have to go to the bathroom!!\n");
			waitStartTime = clock();
			enter(gender, b);
			currState = Peeing;
			printf("Hey my name is Jimmy and I'm in the bathroom!\n");
			bathroomTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevStay) + meanStay  + b.currentTime;
			printf("My name be Jimmy and I'm gonna pee until %f\n", bathroomTime);
		}//if
		else if(currState == Peeing && bathroomTime <= b.currentTime){
			printf("Hey my name is Jimmy, and I'm done using the bathroom!\n");
			leave(b);
			currState = NotPeeing;
			arrivalTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevArrival) + meanArrival + b.currentTime;
			printf("My name be Jimmy and I'm gonna need to pee again at %f\n", arrivalTime);
		}//else if
		else{
			printf("Im Jimmy And I dont Need to Pee\n");
		}
		b.currentTime = (double)(clock() - b.startingTime);
	}//while
	printf("Hey my name is Jimmy and I don't need to go to the bathroom anymore!");
	return NULL;
}//thread()




int main(void){
	//create 1 pthread for the example
	pthread_t jimmy;
	pthread_create(&jimmy, NULL, thread, NULL);
	pthread_join(jimmy, NULL);
	return 0;
}//main
