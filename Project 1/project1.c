/* 
 * Name: Tony Maldonado
 * CS Username: amaldona
 *
 * CS 474: Project 1 - Shared Memory
 * 
 * Date: October 03, 2020
 * 
 * Description: This program will create 4 processes that share a variable 
 * 		named 'total'. Each process will loop and increment by one until 
 * 		the variable reaches 100,000, 200,000, 300,000, and 500,000 in each 
 * 		process respectively. After they have all finished and printed, the 
 * 		parent process will release the shared memory and terminate the 
 * 		program.
 * 
 * Input: None
 * Output: Counters of each process and when each process exits.
 *
 * Preconditions: To be run on the NMSU CS machines.
 * Postconditions: None
 */


# include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

//  Shared memory struct
typedef struct {
	int value;
} shared_mem;

shared_mem *total;

void process1();
void process2();
void process3();
void process4();

int main(){

	// Variable declaration
	int shmid;
	int pid1, pid2, pid3, pid4;
	int status;
	key_t ShmKEY;
	char *shmadd;

	shmadd = (char *) 0;

	ShmKEY = ftok(".", 'x');

	// Create and connect to a shared memory segment
	if ((shmid = shmget(ShmKEY, sizeof(int), IPC_CREAT | 0666)) < 0) {

		perror("shmget");
		exit(1);
	}

	if ((total = (shared_mem *)shmat(shmid, shmadd, 0)) == (shared_mem *)-1) {

		perror("shmat");
		exit(0);
	}

	// Initialize shared memory variable 'total' to 0
	total->value = 0;

	// Create all processes using fork
	// Process 1 creation
	if ((pid1 = fork()) == 0) {
		process1();
	}

	// Process 2 creation
	if ((pid1 != 0) && (pid2 = fork()) == 0) {
		process2();
	}

	// Process 3 creation
	if ((pid1 != 0) && (pid2 != 0) && (pid3 = fork()) == 0) {
		process3();
	}

	// Process 4 creation
	if ((pid1 != 0) && (pid2 != 0) && (pid3 != 0) && (pid4 = fork()) == 0) {
		process4();
	}

	// Wait for child processes to finish 
	waitpid(pid1, status, 0);
	waitpid(pid2, status, 0);
	waitpid(pid3, status, 0);
	waitpid(pid4, status, 0);

	// Once pid's != 0, you know it's the parent process, so print child info
	if ((pid1 != 0) && (pid2 != 0) && (pid3 != 0) && (pid4 != 0)) {

		printf("\n");

		waitpid(pid1);
		printf("Child with ID %d has just exited. \n", pid1);

		waitpid(pid2);
		printf("Child with ID %d has just exited. \n", pid2);

		waitpid(pid3);
		printf("Child with ID %d has just exited. \n", pid3);

		waitpid(pid4);
		printf("Child with ID %d has just exited. \n", pid4);

		// Now detach the shared memory
		if (shmdt(total) == -1){

			perror("shmdt");
			exit(-1);
		}

		// Now remove the shared memory
		shmctl(shmid, IPC_RMID, NULL);
		printf("End of program.\n\n");
	}

}

// These 4 processes will increase the value of 'total' to 100,000, 200,000, 
// 	300,000 and 400,000 respectively, one by one.

// Process 1 incrementation: Increases shared memory variable 'total' to 
// 	100,000 one by one in a loop
void process1() {

	int x = 0;

	while (x <= 100000) {

		total->value = total->value + 1;
		x++;
	}

	printf("\n");
	printf("From Process 1: Counter = %d\n", total->value);
}

// Process 2 incrementation: Increases shared memory variable 'total' to 
// 	200,000 one by one in a loop
void process2() {

	int x = 0;

	while (x <= 200000) {

		total->value = total->value + 1;
		x++;
	}

	printf("From Process 2: Counter = %d\n", total->value);
}

// Process 3 incrementation: Increases shared memory variable 'total' to 
// 	300,000 one by one in a loop
void process3() {

	int x = 0;

	while (x <= 300000) {

		total->value = total->value + 1;
		x++;
	}

	printf("From Process 3: Counter = %d\n", total->value);
}

// Process 3 incrementation: Increases shared memory variable 'total' to 
// 	500,000 one by one in a loop
void process4() {

	int x = 0;

	while (x <= 500000) {

		total->value = total->value + 1;
		x++;
	}

	printf("From Process 4: Counter = %d\n", total->value);
}

