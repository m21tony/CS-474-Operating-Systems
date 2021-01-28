// Name: Tony Maldonado
// Date: November 02, 2020
// Input: A file named 'mytest.dat' which contains characters to be read
// 		  into a buffer by the producer
// Output: A series of the letters produced into the buffer and then
// 		   consumed
// Preconditions: There is a file in the same directory named 'mytest.dat'
// 				  and that compiling and running in the NMSU CS lab machines
// Postconditions: None

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#define _REENTRANT
#define BUFFER_SIZE 15
#define SHMKEY ((key_t) 2700)

void* produce(void* arg);
void* consume(void* arg);

// Buffer struct
typedef struct{ char* value; } sbuffer;
// Counter struct for buffer
typedef struct{ int value; } scounter;

sbuffer *buffer;
scounter *counter;

// You will require 3 sempaphores;
// The buffer should be treated as circular buffer
sem_t empty;
sem_t full;
sem_t critical;

// Global vars for producer and consumer
int start = 0;
int end = 0;

// Character and file input
char newChar;
FILE* fp;

int main (void) {

	// Open the file in read mode
	fp = fopen("mytest.dat", "r");
	
	int i;
	int shmid;
	pthread_t producer[1]; // Process id for producer thread
	pthread_t consumer[1]; // Process id for consumer thread
	pthread_attr_t attr;   // Attribute pointer array

	char *shmadd;
	shmadd = (char *) 0;

	// Create and connect to a shared memory segment
	if ((shmid = shmget (SHMKEY, sizeof(int), IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		return 1;
	}

	if ((buffer = (sbuffer *) shmat (shmid, shmadd, 0)) == (sbuffer *) -1) {
		perror("shmat");
		return 0;
	}

	// This is the circular buffer with 15 positions to be filled 
	// one at a time
	char buffer_array[15];
	buffer->value = buffer_array;

	// Initialize the counter to 0 
	counter = (scounter *) malloc(sizeof(scounter));
	counter->value = 0;

	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);
	sem_init(&critical, 0, 1);

	fflush(stdout);

	// Required to schedule threads independently
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	// End to schedule thread independently

	// Create the threads
	pthread_create(&producer[0], &attr, produce, 0);
	pthread_create(&consumer[0], &attr, consume, 0);

	// Wait for the threads to finish
	pthread_join(producer[0], 0);
	pthread_join(consumer[0], 0);

	// Destory the semaphors after the buffer is full and the file
	// has been completely read
	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&critical);

	if((shmctl(shmid, IPC_RMID, (struct shmid_ds *) 0)) == -1){
		perror("shmctl");
		return -1;
	}

	// Close the input file
	fclose(fp);

	printf("\nParent counter: %d\n", counter->value);
	printf("Done\n");

	return 0;
}

// Producer thread - Fills an empty slot in the buffer and prints to screen
void* produce(void *arg) {

	bool done = false;
	char value;

	while(!done) {
		sem_wait(&empty);
		sem_wait(&critical);
		end++;

		if (fscanf(fp, "%c", &newChar) != EOF) {
			buffer->value[(end) % 15] = newChar;
			printf("Produced: %c\n", newChar);
		}
		else {
			buffer->value[(end) % 15] = '*';
			done = true;
		}

		// Unlock the semaphores
		sem_post(&critical);
		sem_post(&full);
	}
}

// Consumer thread - Removes data from the buffer and prints to screen
void* consume(void *arg) {

	bool done = false;
	char value;

	while (!done) {
		sem_wait(&full);
		sem_wait(&critical);
		start++;

		sleep(1);

		if ((value = buffer->value[(start) % 15]) != '*') {

			printf("Consumed: %c\n", value);
			counter->value++;
		}
		else {
			done = true;
		}

		// Unlock the semaphores
		sem_post(&critical);
		sem_post(&empty);
	}
}