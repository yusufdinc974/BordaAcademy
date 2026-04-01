#include <stdio.h>
#include <math.h>
#define MAX_SIZE 30

// 1. We group the array and its state variables together
typedef struct {
    float buffer[MAX_SIZE];
    int head;       // Write pointer
    int count;      // Tracks how full the buffer is
} CircularBuffer;

// 2. Function to set everything to zero at startup
void initBuffer(CircularBuffer* cb) {
    cb->head = 0;
    cb->count = 0;
    for(int i = 0; i < MAX_SIZE; i++) {
        cb->buffer[i] = 0.0f;
    }
}

float findMin(CircularBuffer* cb){
    if(cb == NULL || cb->count == 0) return 0.0f;
    
    float smallest = cb->buffer[0];
    // Iterate only up to the current count, not MAX_SIZE
    for(int i = 1; i < cb->count; i++){
        if(cb->buffer[i] < smallest){
            smallest = cb->buffer[i];
        }
    }
    return smallest;
}

float findMax(CircularBuffer* cb){
    if(cb == NULL || cb->count == 0) return 0.0f;
    
    float biggest = cb->buffer[0];
    for(int i = 1; i < cb->count; i++){
        if(cb->buffer[i] > biggest){
            biggest = cb->buffer[i];
        }
    }
    return biggest;
}

float findMedian(CircularBuffer* cb){
    if(cb == NULL || cb->count == 0) return 0.0f;

    // 1. Create a local copy
    float temp_arr[MAX_SIZE];
    for(int i = 0; i < cb->count; i++){
        temp_arr[i] = cb->buffer[i];
    }

    // 2. Sort the copy
    for(int i = 0; i < cb->count; i++){
        for(int j = i + 1; j < cb->count; j++){
            if(temp_arr[i] > temp_arr[j]){
                float temp = temp_arr[i];
                temp_arr[i] = temp_arr[j];
                temp_arr[j] = temp;
            }
        }
    }

    // 3. Return the middle of the valid data
    return temp_arr[cb->count / 2];
}

float calculateStandardDeviation(CircularBuffer* cb){
    if(cb == NULL || cb->count <= 1) return 0.0f;

    float sum = 0;
    float sum_difference = 0;

    // Step 1: Calculate Mean
    for(int i = 0; i < cb->count; i++){
        sum += cb->buffer[i];
    }
    float mean = sum / cb->count;

    // Step 2: Calculate Variance
    for(int i = 0; i < cb->count; i++){
        sum_difference += (cb->buffer[i] - mean) * (cb->buffer[i] - mean);
    }

    // Step 3: Return Standard Deviation
    return sqrt(sum_difference / cb->count);
}

// 3. The actual insert function
void insertData(CircularBuffer* cb, float new_data) {
    // Write data to the current head position
    cb->buffer[cb->head] = new_data;
    
    // Advance head using the modulo trick
    cb->head = (cb->head + 1) % MAX_SIZE;
    
    // Increment count until it hits the max size
    if(cb->count < MAX_SIZE) {
        cb->count++;
    }
}

int main() {
    // Create our vault
    CircularBuffer my_vault;
    initBuffer(&my_vault);

    // Simulate 1Hz sensor readings
    insertData(&my_vault, 24.1f);
    insertData(&my_vault, 24.5f);
    
    printf("Next empty slot is at index: %d\n", my_vault.head);
    printf("Total items in buffer: %d\n", my_vault.count);

    return 0;
}