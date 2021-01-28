# CS 474: Project 1

## Description
This program will create 4 processes that share memory and a variable named 'total'. Each process will loop and increment by one until the variable reaches 100,000, 200,000, 300,000, and 500,000 in each process respectively. After they have all finished and printed, the parent process will release the shared memory and terminate the program.

## Compilation

Open a terminal session in one of the NMSU CS Department machines. Then, to compile, run the following command into the terminal session:

```bash
gcc -o project1 project1.c
```

## Usage

To run the program, you first have to compile using the command above. After compilation, to run the program, type the following command into the terminal session:

```bash
./project1
```

## Output
After running, you should get an output that looks like the following:

```bash
From Process 1: Counter = 100000
From Process 2: Counter = 200000
From Process 3: Counter = 300000
From Process 4: Counter = 500000

Child with ID 13011 has just exited. 
Child with ID 13012 has just exited. 
Child with ID 13013 has just exited. 
Child with ID 13014 has just exited. 
End of program.
```

## Information
Written by: Tony Maldonado

Date: October 03, 2020

Written for NMSU CS 474 - Operating Systems 

Professor: Tao Wang