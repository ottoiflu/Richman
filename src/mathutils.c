// src/mathutils.c
#include "mathutils.h"

int mathutils_power(int base, int exponent) {
    if (exponent == 0) {
        return 1;
    }
    
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int mathutils_factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}