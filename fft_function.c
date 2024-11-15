/**
 * @file fft_function.c
 * @brief Functions for Fast Fourier Transform (FFT) algorithm
 * 
 */

#include "fft_function.h"

// Complex addition: (a + bi) + (c + di) = (a + c) + (b + d)i
Complex complex_add(Complex a, Complex b) 
{
    Complex result = { a.real + b.real, a.imag + b.imag };
    return result;
}

// Complex subtraction: (a + bi) - (c + di) = (a - c) + (b - d)i
Complex complex_sub(Complex a, Complex b) {
    Complex result = { a.real - b.real, a.imag - b.imag };
    return result;
}

// Complex multiplication: (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
Complex complex_mul(Complex a, Complex b) {
    Complex result = {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
    return result;
}


// Bit-reversal function for rearranging the array indices
void bit_reverse(Complex *x, int N) {
    int j = 0;
    for (int i = 0; i < N; i++) {
        if (i < j) {
            // Swap x[i] and x[j]
            Complex temp = x[i];
            x[i] = x[j];
            x[j] = temp;
        }
        int m = N >> 1;
        while (m >= 1 && j >= m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
}

void fft_iterative(Complex *x, int N) {
    // First, reorder the input array in bit-reversed order
    bit_reverse(x, N);

    // Iteratively process stages
    for (int s = 1; s <= log2(N); s++) {
        int m = 1 << s;        // Number of points in each sub-FFT
        int half_m = m >> 1;   // Half the number of points for twiddle calculations
        Complex w_m = { cos(2 * PI / m), -sin(2 * PI / m) }; // Twiddle factor e^(-2 * pi / m)

        // For each sub-FFT in this stage
        for (int k = 0; k < N; k += m) {
            Complex w = { 1.0, 0.0 }; // Start with twiddle factor w = 1
            for (int j = 0; j < half_m; j++) {
                // Perform "butterfly" operations
                Complex t = complex_mul(w, x[k + j + half_m]);
                Complex u = x[k + j];
                x[k + j] = complex_add(u, t);
                x[k + j + half_m] = complex_sub(u, t);

                // Update w to the next twiddle factor
                w = complex_mul(w, w_m);
            }
        }
    }
}