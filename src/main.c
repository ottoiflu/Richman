#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

int main() {
    int num1, num2;

    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Invalid input for first number.\n");
        return 1;
    }
    if (scanf("%d", &num2) != 1) {
        fprintf(stderr, "Invalid input for second number.\n");
        return 1;
    }

    int result = add(num1, num2);
    printf("Result: %d\n", result);

    return 0;
}