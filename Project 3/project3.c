// Authors: Gabriella Garcia, Xiana Lara, Antonio Maldonado, Phillip Powell
// Date: November 22, 2020
// CS 474 Project 3: Dining Philosophers Problem

// Define NUM of philosophers, Left side, and Right side.
#define NUM 5
#define LEFT (pNum + 4)%NUM
#define RIGHT (pNum+1)%NUM

// Libraries
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

// Define our eat function in the global space.
void eating(int pNum);

// Define the two semaphores we will be using:
// Mutex, and a sempahore array for the philosophers.
sem_t mutex;
sem_t S[NUM];

// Define global variables, including
// the three statuses of our philosophers:
// Thinking, Hungry, and Ate.
int thinking = 0, hungry = 1, ate = 2;
int status[NUM];
int philos_num[NUM] = {0, 1, 2, 3, 4};


/*********************************************************************
 *  The following methods define eating, taking chopsticks, 
 *  putting chopsticks, and the philosophers themselves.
 *********************************************************************/ 

// Eating Method:
// This method checks to see if the philosopher's status is hungry, and then
// checks to see if the philosophers to the left and right of them do not
// have the ate status. Then we change the status to ate, and print to the
// terminal which philosopher took the chopsticks, and which philosopher is eating.
void eating(int pNum){

    if(status[pNum] == hungry && status[LEFT] != ate && status[RIGHT] != ate){
        status[pNum] = ate;
        sleep(2);
        printf("Philosopher %d takes Chopstick %d and %d and begins to eat.\n", pNum + 1, LEFT + 1, pNum + 1);
        sem_post(&S[pNum]);
    } // end if
} // end eat

void takeChopstick(int pNum) {
    sem_wait(&mutex);
    status[pNum] = hungry;
    printf("Philosopher number %d is Hungry\n", pNum + 1);
    eating(pNum);
    sem_post(&mutex);
    sem_wait(&S[pNum]);
    sleep(1);
} // end function

// Frees up resources for the other processes to function
void placeChopstick(int pNum){
    sem_wait(&mutex);
    status[pNum] = thinking;
    printf("Philosopher %d putting Chopstick %d and %d down and begins to think.\n", pNum + 1, LEFT + 1, pNum + 1);
    eating(LEFT);
    eating(RIGHT);
    sem_post(&mutex);
} // end function

// Represents the philosophers picking up and putting down chopsticks
//  Used in a pthread.
void* philosopher(void *num){
    while(1) {
        int* i = num;
        sleep(1);
        takeChopstick(*i);
        placeChopstick(*i);
    } // end while
} // end function

int main(){
    int i;
    pthread_t thread_id[NUM];
    
    // Initializes the mutex semaphore
    sem_init(&mutex, 0, 1);
    
    // Initializes the chopsticks semaphores
    for(i = 0; i < NUM; i++){
        sem_init(&S[i], 0, 0);
    } // end for
    
    // Creates threads for each philosopher
    for(i = 0; i < NUM; i++){
        pthread_create(&thread_id[i], NULL, philosopher, &philos_num[i]);
        printf("Philosopher %d is Thinking\n", i+1);
    } // end for
    
    for(i = 0; i < NUM; i++) {
        pthread_join(thread_id[i], NULL);
    } // end for
} // end main