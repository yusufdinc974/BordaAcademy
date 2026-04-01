#include <stdio.h>

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