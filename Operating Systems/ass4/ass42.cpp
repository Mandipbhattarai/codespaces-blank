// With Synchronization
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>  // Required for malloc() and free()
#include <time.h>    // For random sleep intervals

int availableSeats;
pthread_rwlock_t rwlock; // Read-write lock for readers
pthread_mutex_t writeMutex; // Mutex for writers

void* reader(void* arg) {
    int reader_id = *(int*)arg;
    usleep(rand() % 50000);  // Add random delay (0-50ms) to mix execution order

    pthread_rwlock_rdlock(&rwlock);  // Acquire read lock
    printf("Reader %d is trying to read available seats.\n", reader_id);
    printf("Reader %d: Available seats = %d\n", reader_id, availableSeats);
    pthread_rwlock_unlock(&rwlock);  // Release read lock

    free(arg);  // Free allocated memory
    return NULL;
}

void* writer(void* arg) {
    int writer_id = *(int*)arg;
    usleep(rand() % 50000);  // Add random delay (0-50ms) to mix execution order

    pthread_mutex_lock(&writeMutex); // Ensures only one writer enters at a time
    pthread_rwlock_wrlock(&rwlock);  // Acquire write lock
    printf("Writer %d is trying to reserve a seat.\n", writer_id);

    if (availableSeats > 0) {
        availableSeats--;
        printf("Writer %d: Seat reserved. Remaining seats = %d\n", writer_id, availableSeats);
    } else {
        printf("Writer %d attempted to reserve a seat, but no seats are available.\n", writer_id);
    }

    pthread_rwlock_unlock(&rwlock);
    pthread_mutex_unlock(&writeMutex);

    free(arg);  // Free allocated memory
    return NULL;
}

int main() {
    srand(time(NULL));  
    int number_of_reader, number_of_writer;
    printf("Enter the available seats.\n");
    scanf("%d",&availableSeats);

    printf("Enter the number of readers.\n");
    scanf("%d",&number_of_reader);

    printf("Enter the number of writers.\n");
    scanf("%d",&number_of_writer);
    
    pthread_t threads[number_of_reader+ number_of_writer];  // 5 Readers + 3 Writers
    int thread_count = 0;

    pthread_rwlock_init(&rwlock, NULL);
    pthread_mutex_init(&writeMutex, NULL);

    // Create mixed threads (random order of readers and writers)
    for (int i = 0; i < number_of_reader; i++) {
        int* id = (int*)malloc(sizeof(int));  
        *id = i + 1;
        pthread_create(&threads[thread_count++], NULL, reader, id);
    }

    for (int i = 0; i < number_of_writer; i++) {
        int* id = (int*)malloc(sizeof(int));  
        *id = i + 1;
        pthread_create(&threads[thread_count++], NULL, writer, id);
    }

    // Join all threads
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);
    pthread_mutex_destroy(&writeMutex);

    return 0;
}