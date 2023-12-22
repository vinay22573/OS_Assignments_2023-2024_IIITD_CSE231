#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
void perform_counting(unsigned long long max_count) {
    unsigned long long count = 0;
    while (count < max_count) {
        count++;
    }
}
void run_child_process(int scheduling_policy, const char* policy_name, unsigned long long max_count, int* hist, double* times, FILE* output_file) {
    if (fork() == 0) {
        sched_setscheduler(getpid(), scheduling_policy, NULL);
        struct timeval start_time, end_time; 
        gettimeofday(&start_time, NULL); 
        perform_counting(max_count);
        gettimeofday(&end_time, NULL); 
        double elapsed_time = difftime(end_time.tv_sec, start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / 1e6;
        fprintf(output_file, "Child Process (%s) Time: %lf\n", policy_name, elapsed_time);
        exit(0);
    }
}
int main() {
    unsigned long long max_count = (1ULL << 32);
    int status;
    int hist_other = 0, hist_rr = 0, hist_fifo = 0;
    double times_other[3], times_rr[3], times_fifo[3];
    FILE *output_file = fopen("custom_execution_times.txt", "w");
    if (output_file == NULL) {
        perror("Error opening file");
        return 1;
    }
    run_child_process(SCHED_OTHER, "SCHED_OTHER", max_count, &hist_other, times_other, output_file);
    wait(&status);
    run_child_process(SCHED_RR, "SCHED_RR", max_count, &hist_rr, times_rr, output_file);
    wait(&status);
    run_child_process(SCHED_FIFO, "SCHED_FIFO", max_count, &hist_fifo, times_fifo, output_file);
    wait(&status);
    fclose(output_file);
    printf("\nCustom Histograms:\n");
    printf("Custom SCHED_OTHER: %d\n", hist_other);
    printf("Custom SCHED_RR: %d\n", hist_rr);
    printf("Custom SCHED_FIFO: %d\n", hist_fifo);
    return 0;
}
