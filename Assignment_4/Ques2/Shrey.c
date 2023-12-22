#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PASSENGERS 100

// Global variables
int total_passengers;
int car_capacity;
int boarded_passengers = 0;
int ride_done_or_not_started = 1; // Initialized with 1
pthread_mutex_t mutex;
sem_t loaded_sem, unloading_done_sem, boarded_sem;
pthread_cond_t board_cv; // Condition variable for boarding
pthread_cond_t loaded_cv; // Condition variable for loading

void load() {
    pthread_mutex_lock(&mutex);  // Use pthread_mutex_lock instead of sem_wait
    printf("Loading Passenger.\n");
    sem_post(&loaded_sem);
    pthread_cond_broadcast(&loaded_cv);
    pthread_mutex_unlock(&mutex); // Use pthread_mutex_unlock instead of sem_post
}

void board(int id) {
    sem_wait(&loaded_sem);
    pthread_mutex_lock(&mutex); // Use pthread_mutex_lock instead of sem_wait
    boarded_passengers++;
    printf("Passenger with id %d is boarded.\n", id);
    sem_post(&mutex);
    sem_post(&boarded_sem);
    pthread_cond_broadcast(&board_cv);
    pthread_mutex_unlock(&mutex); // Use pthread_mutex_unlock instead of sem_post
}

void *passenger(void *args) {
    int id = *((int *)args);
    pthread_mutex_lock(&mutex);
    while (boarded_passengers < car_capacity) {
        pthread_cond_wait(&board_cv, &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

void run(void *arg) {
    int time = *((int *)arg);
    load();
    pthread_mutex_lock(&mutex);
    ride_done_or_not_started = 0;
    printf("Car is running.\n");
    sleep(10);
    sem_post(&unloading_done_sem);
    pthread_mutex_unlock(&mutex);
}

void unload() {
    sem_wait(&unloading_done_sem);
    pthread_mutex_lock(&mutex);
    printf("Unloaded Passenger.\n");
    pthread_mutex_unlock(&mutex);
}

void offboard(int id) {
    sem_wait(&unloading_done_sem);
    pthread_mutex_lock(&mutex);
    printf("Passenger with id %d is unboarded.\n", id);
    boarded_passengers--;
    sem_post(&boarded_sem);
    pthread_cond_broadcast(&board_cv);
    pthread_mutex_unlock(&mutex);
}

void *car(void *arg) {
    while (1) {
        run(arg);
        sleep(5);
    }
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
    sem_init(&loaded_sem, 0, 0);
    sem_init(&unloading_done_sem, 0, 0);
    sem_init(&boarded_sem, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Initialize condition variables
    pthread_cond_init(&board_cv, NULL);
    pthread_cond_init(&loaded_cv, NULL);

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
    sem_destroy(&loaded_sem);
    sem_destroy(&unloading_done_sem);
    sem_destroy(&boarded_sem);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&board_cv);
    pthread_cond_destroy(&loaded_cv);

    return 0;
}
