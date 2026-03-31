#include <stdio.h>
#include <stddef.h>

// Define a maximum window size for our buffer to prevent memory issues
#define WINDOW_SIZE 5 

float medianFilter(float* arr, int range){
    // Safety check: Don't process null arrays or invalid ranges
    if(arr == NULL || range <= 0 || range > WINDOW_SIZE) return -1.0f;

    // 1. Create a local copy so we don't destroy the chronological timeline!
    float temp_arr[WINDOW_SIZE];
    for(int i = 0; i < range; i++){
        temp_arr[i] = arr[i];
    }

    // 2. Your exact sorting logic (applied to the copy)
    for(int i = 0; i < range; i++){
        for(int j = i + 1; j < range; j++){
            if(temp_arr[i] > temp_arr[j]){
                // Swap
                float temp = temp_arr[i];
                temp_arr[i] = temp_arr[j];
                temp_arr[j] = temp;
            }
        }
    }

    // 3. Return the exact middle of the sorted copy
    return temp_arr[range / 2];
}

int main(){
    // Simulating chronological sensor data (notice the 85.0 noise spike)
    float raw_sensor_buffer[WINDOW_SIZE] = {24.1, 24.5, 85.0, 24.2, 24.3};
    
    float clean_value = medianFilter(raw_sensor_buffer, WINDOW_SIZE);
    
    printf("Filtered Median Value: %.2f\n", clean_value);
    
    // The original buffer is still perfectly intact for the next reading!
    printf("Original Oldest Value: %.2f\n", raw_sensor_buffer[0]); 

    return 0;
}