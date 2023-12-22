#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5
int bowl = 2;
pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_cond_t condBowl;
pthread_mutex_t mutex;
pthread_mutex_t mtex;
int left(int p) {
    return p;
}
int right(int p) {
    return (p + 1) % NUM_PHILOSOPHERS;
}
void get_Bowl(int p){
    pthread_mutex_lock(&mutex);
    while(bowl < 1){
        pthread_cond_wait(&condBowl,&mutex);
    }
    bowl -= 1;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&condBowl);
}
void put_Bowl(int p){
    pthread_mutex_lock(&mutex);
    bowl +=1;
    pthread_mutex_unlock(&mutex);    
}
// function to get the left and right forks
void get_foods(int p) {
    get_Bowl(p);
    if (p == (NUM_PHILOSOPHERS)-1) {// case where highest is given right fork first to avoid deadlock
        pthread_mutex_lock(&forks[left(p)]);
        pthread_mutex_lock(&forks[right(p)]);
    } else { // for general cases
        pthread_mutex_lock(&forks[left(p)]);
        pthread_mutex_lock(&forks[right(p)]);
    }
    
}
// function to put the left and right forks
void put_foods(int p) {
    put_Bowl(p);
    pthread_mutex_unlock(&forks[left(p)]);
    pthread_mutex_unlock(&forks[right(p)]);
}
void think(int philosopher_id) {
    printf("Philosopher %d is thinking.\n", philosopher_id);
    sleep(1); // Simulating thinking time
}
void eat(int philosopher_id) {
    printf("Philosopher %d is eating.\n", philosopher_id);
    sleep(1); // Simulating eating time
}
void *philosopher(void* arg) {
    int philosopher_id = *(int*)arg;
    while (1) {
        think(philosopher_id);
        get_foods(philosopher_id);
        eat(philosopher_id);
        put_foods(philosopher_id);
    }
    return NULL;
}
int main(){
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    // pthread_mutex_init(&mutex,NULL);    
    pthread_cond_init(&condBowl, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_init(&forks[i], NULL);
    }
    // Create philosopher threads
    //Given below is a way to create threads using loops
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_ids[i] = i;
        // &philosphers[i] or philosphers + 1
        // at the time of thread creation you give address
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }
    // Wait for philosopher threads to finish (this won't happen in a real implementation)
    
    // at the time of join you actually dont give address of the thread you give value
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}




















// CASES WHERE DEADLOCK WAS OCCURING IN GET AND OUT BOWLS 

// // #define NUM_BOWL 2
// // sem_t Bowls[NUM_BOWL];
// // function to get the left and right forks
// void get_foods(int p) {
    
//     // if (p == (NUM_PHILOSOPHERS)-1) {// case where highest is given right fork first to avoid deadlock
//     //     sem_wait(&forks[right(p)]);
//     //     sem_wait(&forks[left(p)]);
//     // } else { // for general cases
//     // IF WE WOULD HAVE NOT USED SPECIAL CASE FOR LAST PHILOSPHERS THEN ERROR WOULD HAVE OCCURED
//         sem_wait(&forks[left(p)]);
//         sem_wait(&forks[right(p)]);
//     // }
//     sem_wait(&Bowls[p]);
// }

// // function to put the left and right forks
// void put_foods(int p) {
//     sem_post(&Bowls[p]);
//     sem_post(&forks[left(p)]);
//     sem_post(&forks[right(p)]);
// }