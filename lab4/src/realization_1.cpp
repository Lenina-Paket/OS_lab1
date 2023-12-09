#include "../include/realization.hpp"

float Derivative(float A, float deltaX) {
    return (cosf(A + deltaX) - cosf(A)) / deltaX;
}

int GCF(int A, int B) {
    while (A != 0 && B != 0) {
        if (A > B) {
            A = A % B;
        } else {
            B = B % A;
        }
    }
    return A + B;
}