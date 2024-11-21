/**
 * @file tunning_algorithm.c
 * @brief Definition of the tunning algorithm functions
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "find_tune.h"

float frequency_current = 0.0;
float frequency_ratio = 0.0;
float target_frequency = 0.0;

// Function to find the main frequency
float find_main_frequency(Complex *X, int N, float sampling_rate) {
    int max_index = 1;  // Start from 1 to ignore DC component (index 0)
    float max_magnitude = 0.0;

    // Loop through the FFT result to find the largest magnitude
    for (int k = 1; k < N / 2; k++) {  // Only up to N/2 because of symmetry
        float magnitude = sqrtf(X[k].real * X[k].real + X[k].imag * X[k].imag);
        if (magnitude > max_magnitude) {
            max_magnitude = magnitude;
            max_index = k;
        }
    }

    // Calculate the corresponding frequency
    float main_frequency = max_index * sampling_rate / N;
    return main_frequency;
}

void find_tune_function(uint32_t* buffer, uint32_t buffer_size)
{
    // 1. Analyze the frequency of the input wave
    // Call to FFT iterative function to convert the waveform into the frequency domain
    fft_iterative(buffer, buffer_size);

    // 1.2 Identify the dominant frequency component in the frequency domain
    frequency_current = find_main_frequency(buffer, buffer_size, 44100);
    
    // 2. Adjust the frequency to match the desired note
    // 2.1 Calculate the frequency ratio between current frequency and target frequency
    frequency_ratio = target_frequency / frequency_current;

    // 2.2 Change frequency: time stretching (if target frequency is lower) or compression (if target frequency is higher)
    if(frequency_ratio < 1.0)
    {
        time_stretch(); // Time stretching
    }
    else
    {
        time_compression();// Time compression     
    }
        // Time stretching
    // 2.3 Reconstruction of the waveform in the time domain


}