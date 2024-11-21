/**
 * @file find_tune.h
 * @brief Header file for the tunning algorithm functions
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "fft_function.h"

/**
 * @brief Function to implement the tunning algorithm: 
 * 1. Analyze the frequency of the input wave
 * 1.1 Convert the waveform from the time domain into the frequency domain by using the Fast Fourier Transform (FFT)
 * 1.2 Identify the dominant frequency component in the frequency domain
 * 2. Adjust the frequency to match the desired note
 * 2.1 Calculate the frequency ratio between current frequency and target frequency
 * 2.2 Change frequency: time stretching (if target frequency is lower) or compression (if target frequency is higher)
 * 2.3 Reconstruction of the waveform in the time domain
 * 
 * @param buffer The array containing the input waveform
 * @param buffer_size Size of the input waveform array
 */
void find_tune_function(uint32_t* buffer, uint32_t buffer_size);