**Caleb Stanberry**   
**CS 33211**   
**Assignment 1**   
**Producer and Consumer**   

Files:
- producer.cpp
- consumer.cpp

**Program Description**   
This program implements the Producer-Consumer problem using POSIX semaphores and shared memory for inter-process communication on a Linux system.

The Producer process first creates a shared memory region and initializes three semaphores to synchronize access. Items are produced by placing them into a table (represented as a buffer with 2 slots in shared memory). The Consumer process attaches to the same shared memory and removes items when available.

The table can hold only two items at once, with the producer waiting when the table is full and the consumer waiting when it is empty. Both processes use mutual exclusion (mutex) to prevent simultaneous access to the shared buffer. When run, the programs produce and consume items at slightly different rates, showing  synchronization behavior.

Example Executed Results:   
Producer start   
Consumer start   
Produced item in slot 0   
Consumed item in slot 0   
Produced item in slot 0   
Produced item in slot 1   
Consumed item in slot 0   
Consumed item in slot 1   
Produced item in slot 0   
Consumed item in slot 0   
Produced item in slot 0   
Consumed item in slot 0   
Produced item in slot 0   
Producer done   
Consumed item in slot 0   
Consumer done   

**Usage Instructions**   
System requirements:
Linux system
G++ compiler and real-time libraries installed

Run in the terminal to compile:
g++ producer.cpp -pthread -lrt -o producer
g++ consumer.cpp -pthread -lrt -o consumer

Run in the terminal to execute:
./producer & ./consumer &

**Explanation of Key Components**   
Shared Memory: Created using shm_open, ftruncate, and mmap. Acts as the table shared between producer and consumer. Holds a buffer of size 2.

Semaphores: Three POSIX semaphores are used:
- /fill: counts how many slots are full (initially 0)
- /avail: counts how many slots are empty (initially 2)
- /mutex: enforces mutual exclusion so only one process can be in shared memory at a time
