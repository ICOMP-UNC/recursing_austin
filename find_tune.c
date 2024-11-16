/**
 * @file tunning_algorithm.c
 * @brief Definition of the tunning algorithm functions
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "find_tune.h"

// Function to find the main frequency
float find_main_frequency(Complex *X, int N, float sampling_rate) 
{
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

void convert_to_complex(uint32_t *adc_buffer, Complex *complex_buffer, uint32_t buffer_size) 
{
    // Allocate memory for the Complex array
    Complex *complex_array = (Complex *)malloc(buffer_size * sizeof(Complex));

    for (uint16_t i = 0; i < buffer_size; i++)
    {
        complex_buffer[i].real = (float)adc_buffer[i]; // Assign ADC value to real part
        complex_buffer[i].imag = 0.0f;               // Set imaginary part to 0
    }
}

void find_tune_function(uint32_t *buffer, uint32_t buffer_size) 
{
    convert_to_complex(buffer, complex_buffer, buffer_size);

  // 1. Analyze the frequency of the input wave
  // Call to FFT iterative function to convert the waveform into the frequency
  // domain
  fft_iterative(buffer, buffer_size);

  // 1.2 Identify the dominant frequency component in the frequency domain
  frequency_current = find_main_frequency(buffer, buffer_size, ADC_FREQ);

  // Free the memory allocated for the Complex array
  free(complex_buffer);
}