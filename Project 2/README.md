# CS 474: Project 2

## Description

This program will teach us about how to use semaphores to protect a limited size resource. A circular buffer with 15 positions for characters will be used to communicate information between threads, a producer and a consumer. 
The producer will read characters until the end of file and print to screen and inform the consumer when to consume the buffer. The producer does this by placing a special character into the shared buffer - * - then the consumer knows to start consuming. As the consumer reads the characters, it will print to the screen.


## Compilation

Open a terminal session in one of the NMSU CS Department machines. Then, to compile, run the following command into the terminal session:

```bash
gcc project2.c -lpthread -lpr 
```

## Usage

Before running, be sure to have the test file 'mytest.dat' in the same directory that you have the 'program2.c' file in.

Then, to run the program, you first have to compile using the command above. After compilation, to run the program, type the following command into the terminal session:

```bash
./a.out 
```

## Output
After running, you should get an output that looks like the following:

```bash
Produced: H
Produced: e
Produced: l
Produced: l
Produced: o
Produced: W
Produced: o
Produced: r
Produced: l
Produced: d
Produced: M
Produced: y
Produced: N
Produced: a
Produced: m
Consumed: H
Consumed: e
Consumed: l
Consumed: l
Consumed: o
Consumed: W
Consumed: o
Consumed: r
Consumed: l
Consumed: d
Consumed: M
Consumed: y
Consumed: N
Consumed: a
Consumed: m
...

Parent counter: 35

Done
```

## Information
Written by: Tony Maldonado

Date: November 03, 2020

Written for NMSU CS 474 - Operating Systems 

Professor: Tao Wang