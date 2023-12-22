”””Dining Philosophers Problem
This C program illustrates the classic dining philosophers problem, a synchronization and concurrency problem in computer science. The scenario involves a finite set of philosophers sitting around a dining table with bowls of food. The philosophers alternate between thinking and eating, but they must use shared resources (bowls and forks) to eat. The challenge is to avoid deadlock and contention while ensuring that each philosopher gets a chance to eat.
Implementation Details
Files
dining_philosophers.c(Q1.c): The main C file containing the implementation of the dining philosophers problem.
Dependencies
This program uses the pthread library for thread creation and synchronization.
The program assumes a Unix-like environment due to the usage of pthreads and related synchronization mechanisms.


Description
The program defines a fixed number of philosophers (NUM_PHILOSOPHERS) and a shared resource, the bowl, which is initially set to 2.
Each philosopher is represented as a thread and has its own unique identifier.
The program uses mutex locks and condition variables to control access to shared resources, ensuring that philosophers can pick up and put down forks and the bowl in a coordinated manner.
Philosophers alternate between thinking, picking up forks, eating, and putting down forks, with proper synchronization to avoid deadlocks and contention.
Functions
think: Simulates the philosopher thinking by printing a message and sleeping for a short duration.
eat: Simulates the philosopher eating by printing a message and sleeping for a short duration.
get_forks: Acquires the left and right forks for a philosopher, avoiding deadlock by ensuring a specific order of acquisition.
put_forks: Releases the left and right forks after the philosopher has finished eating.
get_bowl and put_bowl: Acquires and releases the shared bowl, ensuring proper synchronization.
Synchronization Mechanisms
Mutex locks: Used to protect access to forks, the bowl, and other critical sections to avoid race conditions.
Condition variables: Used to signal when resources (forks, bowl) are available or when philosophers have finished using them.”””