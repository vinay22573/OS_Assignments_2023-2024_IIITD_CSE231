#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PASSENGERS 100
// unitialized
int total_passengers;
int car_capacity;
pthread_cond_t board_load; // for broadcasting about load is done to the passenger
pthread_cond_t unboard_load;
int load_done = 0; // flag which is used to check if load is done or not
int boarded_passengers = 0; // variable to check boarded passengers till now
sem_t boared_mutex; // lock used in board function
sem_t load_mutex;// for locking and unlocking in load
sem_t unload_mutex;
pthread_mutex_t board_mutex;
sem_t is_passenger_boarded;

void load(){
    sem_wait(&load_mutex);
    load_done = 1;
    printf("Load done.\n");
    sem_post(&load_mutex);
    pthread_cond_broad(&board_load);
    
}






// board has to check on its own that whether loading is done or not
void board(int id){
    pthread_mutex_lock(&board_mutex);
    while(load_done == 0){
        pthread_cond_wait(&board_load,&board_mutex);
    }
    pthread_mutex_unlock(&board_mutex);
    sem_wait(&boared_mutex);
    boarded_passengers++;
    printf("Passenger with id %d is boarded.\n", id);
    sem_post(&boared_mutex);
    sem_post(&is_passenger_boarded); // tell it that the passenger is boarded for which they were waiting 
}



void unload(){
    sem_wait(&unload_mutex);
    load_done = 0;
    printf("Unload done.\n");
    sem_post(&unload_mutex);
    pthread_cond_broad(&unboard_load);

}
void offboard(int id){
    pthread_mutex_lock(&board_mutex);
    while(load_done == 1){
        pthread_cond_wait(&board_load,&board_mutex);
    }
    pthread_mutex_unlock(&board_mutex);
    sem_wait(&boared_mutex);
    boarded_passengers++;
    printf("Passenger with id %d is boarded.\n", id);
    sem_post(&boared_mutex);
    sem_post(&is_passenger_boarded); // tell it that the passenger is boarded for which they were waiting 
}



// for now we are not including the part where the time of car running is shown just focussing on synchronization
void run(void *arg){
    int time = *((int *)arg);
    load();
    // look anyhow use the passenger thread to board the number passnegers for car capacity

    
    

}








int main() {
    // Input from the user
    printf("Enter the total number of passengers: ");
    if (scanf("%d", &total_passengers) != 1) {
        printf("Error reading the total number of passengers.\n");
        return 1;
    }

    printf("Enter the car capacity: ");
    if (scanf("%d", &car_capacity) != 1) {
        printf("Error reading the car capacity.\n");
        return 1;
    }

    // Validate input
    if (car_capacity <= 0 || car_capacity > total_passengers) {
        printf("Invalid input. Car capacity should be greater than 0 and less than the total number of passengers.\n");
        return 1;
    }

    // Initialize semaphores and mutex
    /*
    // sem_init(&loaded_sem, 0, 0);
    // sem_init(&unloading_done_sem, 0, 0);
    // sem_init(&boarded_sem, 0, 0);
    // pthread_mutex_init(&mutex, NULL);

    // Initialize condition variables
    // pthread_cond_init(&board_cv, NULL);
    // pthread_cond_init(&loaded_cv, NULL);
    */

    // Create car and passenger threads
    pthread_t car_thread;
    pthread_create(&car_thread, NULL, car, NULL);

    pthread_t passenger_threads[MAX_PASSENGERS];
    for (int i = 0; i < total_passengers; i++) {
        int *passenger_id = malloc(sizeof(int));
        *passenger_id = i + 1;
        pthread_create(&passenger_threads[i], NULL, passenger, passenger_id);
    }

    // Join threads
    pthread_join(car_thread, NULL);
    for (int i = 0; i < total_passengers; i++) {
        pthread_join(passenger_threads[i], NULL);
    }

    // Destroy semaphores, mutex, and condition variables

    /*
    sem_destroy(&loaded_sem);
    sem_destroy(&unloading_done_sem);
    sem_destroy(&boarded_sem);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&board_cv);
    pthread_cond_destroy(&loaded_cv);
    */

    return 0;
}