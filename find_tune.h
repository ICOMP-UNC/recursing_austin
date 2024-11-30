/**
 * @file find_tune.h
 * @brief Header file for the tunning algorithm function and a function 
 * to convert the adc readings into complex values
 * 
 */

#include "fft_function.h"

float frequency_current = 0.0;  // Frequency of the analyzed sound.

Complex complex_buffer[SIZE_BUFFER_ADC] = {0}; // Complex buffer to store the ADC results

/**
 * @brief Convert the ADC readings into complex values.
 * 
 * @param adc_buffer 
 * @param complex_buffer 
 * @param buffer_size 
 */
void convert_to_complex(uint32_t *adc_buffer, Complex *complex_buffer, uint32_t buffer_size);

/**
 * @brief Find the main frequency of the input.
 * 
 * @param X The value to analyze.
 * @param N Size of the input array.
 * @param sampling_rate Rate of the sampling from the ADC.
 * @return float 
 */
float find_main_frequency(Complex *X, int N, float sampling_rate);

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
void find_tune_function(uint32_t* adc_buffer, uint32_t buffer_size);