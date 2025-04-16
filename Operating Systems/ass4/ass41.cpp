//Code without Synchronization 

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int availableSeats;  // Shared resource

// Reader thread function
void* reader(void* arg) {
    int reader_id = *(int*)arg;
    printf("Reader %d is trying to read available seats.\n", reader_id);
    printf("Reader %d: Available seats = %d\n", reader_id, availableSeats);
    return NULL;
}
                                                  
// Writer thread function
void* writer(void* arg) {
    int writer_id = *(int*)arg;
    printf("Writer %d is trying to reserve a seat.\n", writer_id);
    availableSeats--;
    printf("Writer %d: Seat reserved. Remaining seats = %d\n", writer_id, availableSeats);
    return NULL;
}

int main() {
    int number_of_reader, number_of_writer;
    printf("Enter the available seats.\n");
    scanf("%d",&availableSeats);

    printf("Enter the number of readers.\n");
    scanf("%d",&number_of_reader);

    printf("Enter the number of writers.\n");
    scanf("%d",&number_of_writer);

    
    pthread_t readers[number_of_reader], writers[number_of_writer];
    int reader_ids[number_of_reader], writer_ids[number_of_writer];
    
    // Create reader threads
    for (int i = 0; i < number_of_reader; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < number_of_writer; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join reader threads
    for (int i = 0; i < number_of_reader; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < number_of_writer; i++) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}
