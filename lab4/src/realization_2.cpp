#include "../include/realization.hpp"

float Derivative(float A, float deltaX) {
    return (cosf(A + deltaX) - cosf(A - deltaX)) / (2 * deltaX);
}

int GCF(int A, int B) {
    int del = 1, max;
    while (del <= A and del <= B) {
        if ((A % del == 0) and (B % del == 0)) {
            max = del;
        }
        del++;
    }
    return max;
}