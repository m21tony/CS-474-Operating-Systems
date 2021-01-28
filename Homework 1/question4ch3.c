#include<stdio.h>

int main(){

	int m = 10, n = 5,count = 1, mult = 1;
	//int parent = 0;
	//int child = 0;

	while(count < 3){
		if(m != 0) {
			m = fork(); 
			n = n + 25;
			//parent = parent + 1;
			//printf("Parent: %d\n", parent);
		} else {
			m = fork();
			n = n + 20;
			mult = mult * n;
			//child = child + 1;
			//printf("Child: %d\n", child);
		}

	printf(" n = %d mult = %d\n", n, mult);
	count = count + 1;
	}
}