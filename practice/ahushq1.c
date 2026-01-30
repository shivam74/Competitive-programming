#include <stdio.h>
#include <stdlib.h>

// Changed to long long to prevent overflow with large constraints
long long result = -1;
long long inter_sum = -1;

// Recursive helper for Multiplication using addition
void multiplyRecursive(long long a, long long b, long long current_val, int step) {
    if (step == b) {
        result = current_val;
        return;
    }
    // Add 'a' to the current value for the next intermediate result
    current_val += a;
    inter_sum += current_val;
    multiplyRecursive(a, b, current_val, step + 1);
}

// Recursive helper for Division using subtraction
void divideRecursive(long long a, long long b, int count) {
    // Base case: if remainder is less than divisor, division is done
    if (a < b) {
        result = count;
        return;
    }
    // Subtract 'b' from 'a' to get the intermediate result
    a -= b;
    inter_sum += a;
    divideRecursive(a, b, count + 1);
}

void solveExpression(char *s) {
    long long a, b;
    char op;

    // Parse the input string (e.g., "10/2" or "10*4")
    // sscanf handles the lack of spaces automatically
    if (sscanf(s, "%lld %c %lld", &a, &op, &b) < 3) {
        sscanf(s, "%lld%c%lld", &a, &op, &b);
    }

    inter_sum = 0; // Reset sum for current calculation

    if (op == '*') {
        if (b == 0) {
            result = 0;
            inter_sum = 0;
        } else if (b == 1) {
            result = a;
            inter_sum = 0;
        } else {
            // Start with the first value and iterate b-1 times
            multiplyRecursive(a, b, a, 1);
        }
    } else if (op == '/') {
        if (b == 0) {
            result = 0; // Division by zero safety
        } else {
            divideRecursive(a, b, 0);
        }
    }
}

int main() {
    char *s = (char*)malloc(sizeof(char) * 100);
    
    // Read input until whitespace
    if (scanf("%s", s) == 1) {
        solveExpression(s);
        
        // Use %lld to match the long long variable type
        printf("%lld\n%lld", result, inter_sum);
    }
    
    free(s);
    return 0;
}