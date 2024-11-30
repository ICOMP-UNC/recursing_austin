/**
 * @file fft_function.h
 * @brief Header file for the FFT function and other related functions.
 * 
 */

#ifndef FFT_FUNCTION_H
#define FFT_FUNCTION_H


#include <math.h>
#include <stdint.h> // For using standard integer types like int32_t

#define PI 3.14159265358979323846

// Define a complex number structure
typedef struct {
    float real;
    float imag;
} Complex;

// Function prototypes

// Complex addition: (a + bi) + (c + di) = (a + c) + (b + d)i
Complex complex_add(Complex a, Complex b);

// Complex subtraction: (a + bi) - (c + di) = (a - c) + (b - d)i
Complex complex_sub(Complex a, Complex b);

// Complex multiplication: (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
Complex complex_mul(Complex a, Complex b);

// Bit-reversal function for rearranging the array indices
void bit_reverse(Complex *x, int N);

// Fast Fourier Transform (FFT) algorithm
void fft_iterative(Complex *x, int N);



#endif // FFT_FUNCTION_H