#include <math.h>
#include "pav_analysis.h"

#define M_PI 3.14159265358979323846

float compute_power(const float *x, unsigned int N) {
    float suma = 1e-6;
    for(int i = 0; i < N; i++){
        suma += x[i] * x[i];
    }
    return 10*log10(suma);
}

float compute_am(const float *x, unsigned int N) {
    float suma = 0.0;
    for(int i = 0; i < N; i++){
        suma += fabs(x[i]);
    }
    return suma/N;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    int suma = 0;
    for(int i = 1; i < N; i++){
            suma += (x[i] * x[i-1] < 0);
    }
    return fm*suma/(2*(N-1));
}

float hamming_window(int n, int M){
    return (float) 0.54 - 0.46*cos(2*M_PI*n/(M-1));
}
