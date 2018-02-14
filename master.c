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
	int threadNumber;
} inputStruct;

void *thread(void *voidIn) {
	inputStruct *structIn = voidIn;
	int gender = structIn->genIn;
	double meanArrival = structIn->arrivalIn; //the mean arrival time
	double stddevArrival = meanArrival / 2;
	double meanStay = structIn->stayIn; //the average time that people stay
	double stddevStay = meanStay/2;
	int loopCount = structIn->loopsIn;//the number of times the person is meant to go to the bathroom
	int number = structIn->threadNumber;
	int numLoops = loopCount;
	int currState = NotPeeing;

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

	double bathroomTime;
	double arrivalTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevArrival) + meanArrival + b.time;


	printf("Im %d And My First Pee Time: %f\n", number, arrivalTime);
	printf("Im %d And My Loop Count Is: %d\n", number, loopCount);
	while(loopCount > 0){
		if(currState == NotPeeing && arrivalTime <= b.time){
			//printf("Hey my name is %d and I have to go to the bathroom!!\n", number);
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
			//printf("Hey my name is %d and I'm in the bathroom!\n", number);
			bathroomTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevStay) + meanStay  + b.time;
			//printf("My name be %d and I'm gonna pee until %f\n", number, bathroomTime);
		}//if
		else if(currState == Peeing && bathroomTime <= b.time){
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
			arrivalTime = ((sqrt(-2 * log(drand48())) * cos(2 * 3.14 * drand48())) * stddevArrival) + meanArrival + b.time;
			loopCount--;
			//printf("My name be %d and I'm gonna need to pee again at %f\n", number, arrivalTime);
		}//else if
		else if(currState == Peeing && bathroomTime > b.time){
			//printf("My name be %d and Oni-Chan is being a perv\n", number);
		}
		else{
			//printf("Im %d And I dont Need to Pee Until  %f\n", number, arrivalTime);
		}

		//to keep the time updated, after anyone goes through an operation, we check the time.
		usleep(1000);
		gettimeofday(&b.currentTime, NULL);
		b.time = (b.currentTime.tv_sec - b.startTime.tv_sec) + ((b.currentTime.tv_usec - b.startTime.tv_usec)/1000000.0);
		//printf("Current Time: %f -------------------\n", b.time);
		//printf("Im %d and I have %d Loops Remaining\n", number, loopCount);
		b.incrementer++;//increment the tracker; every loop this increments as well as the other bathroom/line stuff for the sake of finding the average
		b.bathroomPeople = b.bathroomPeople + b.currentPeopleCount;//match the incrementer with this
		b.linePeople = b.linePeople + b.lineCount;
	}//while
	printf("Hey my name is %d and I don't need to go to the bathroom anymore!\n", number);
	printf("Hey my name is %d and my longest wait time was %d, my shortest wait time was %d, and my average wait time was %d\nOn top of that, my longest time in the bathroom was %d, my shortest time in the bathroom was %d, and my average time in the bathroom was %d");
	return NULL;
} //thread()


void finalize(int totalTrips, int incrementer, int bathroomPeople, int linePeople, double endingTime, double emptyTime, double longestWait, double shortestWait, double meanWait, double longestBath, double shortestBath, double meanBath){
	printf("There were %d trips to the bathroom on this day\n", totalTrips);
	double lineAverage = linePeople / incrementer;
	double bathroomAverage = bathroomPeople / incrementer;
	printf("The average number of people in the line at any given point was %d\nThe average number of people in the bathroom at any given point was %d\n", lineAverage, bathroomAverage);
	double populatedTime = endingTime - emptyTime;//since this is run after the code, the last value of b.time will be the total runtime
	printf("The amount of time that the bathroom was populated was %d\nThe amount of time that the bathroom was empty was %d\n", populatedTime, emptyTime);
	printf("The overall longest wait time was %d\nThe overall shortest wait time was %d\nThe overall mean wait time was %d", longestWait, shortestWait, meanWait);
	printf("The overall longest time in the bathroom was %d\nThe overall shortest time in the bathroom was %d\nThe overall mean time in the bathroom was %d", longestBath, shortestBath, meanBath);
}

int main(int argc, char *argv[]){
	int threadCount = 20000;
	int meanLoop = 9000;
	double meanArrival = 10;
	double meanStay = 5;
	pthread_t* threadIDs = (pthread_t*)calloc(sizeof(pthread_t), threadCount);
	inputStruct* threadInfo = calloc(threadCount, sizeof(inputStruct));
	srand48((int)(time(NULL)));

	//Init the bathroom, things that cant be done in init get done here as well
	init(b);
	gettimeofday(&b.startTime, NULL);
	gettimeofday(&b.currentTime, NULL);
	b.time = (b.currentTime.tv_sec - b.startTime.tv_sec) + ((b.currentTime.tv_usec - b.startTime.tv_usec)/1000000.0);
	pthread_spin_unlock(&b.lock);
	printf("Start Time: %f\n", b.time);

	//bathroomSim nUsers meanLoopCount meanArrival meanStay
	if(argc != 5){
		printf("Invalid Parameter Count\nUsage: \'./bathroomSim nUsers meanLoopCount meanArrival meanStay\'\n");
		exit(-1);
	}
	else{
		threadCount = atoi(argv[1]);
		meanLoop = atoi(argv[2]);
		meanArrival = atof(argv[3]);
		meanStay = atof(argv[4]);
	}


	for(int i = 0; i < threadCount; i++){
		threadInfo[i].genIn = (rand()%1)+1; //has to return 1 or 2 in order to be male or female
		threadInfo[i].arrivalIn = meanArrival;
		threadInfo[i].stayIn = meanStay;
		threadInfo[i].loopsIn = meanLoop;
		threadInfo[i].threadNumber = i;

		pthread_create(&threadIDs[i], NULL, thread, &threadInfo[i]);
//		makeNewThread((i%2)+1, meanArrival, meanStay, 1000, i , &threadIDs[i]);
	}
	for(int i = 0; i < threadCount; i++){
		pthread_join(threadIDs[i], NULL);
	}
	finalize(b.bathroomTrips, b.incrementer, b.bathroomPeople, b.linePeople, b.time, b.emptyTime, b.longestWait, b.shortestWait, b.meanWait, b.longestBath, b.shortestBath, b.meanBath);//run the finalize function
	return 0;
} //main
