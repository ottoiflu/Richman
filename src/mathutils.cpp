// src/mathutils.cpp
#include "mathutils.h"

int MathUtils::power(int base, int exponent) {
    if (exponent == 0) {
        return 1;
    }
    
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int MathUtils::factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}