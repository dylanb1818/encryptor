#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

char* ASCII_val(char c);
int find_pq(int lower, int upper);
bool isPrime(int n);
int GCD(int num1, int num2);
int calculate_e(long long int lambda);
int extended_euclidean(int e, int lambda, int *x, int *y);
int calculate_d(int e, int lambda);
int read_msg();

int main()
{   
    long long int p = find_pq(1000000, 10000000);
    long long int q = find_pq(100000000, 1000000000);    
    long long int n = p * q;
    long long int gcd = GCD(p-1, q-1);
    long long int lambda = ((p-1)*(q-1))/gcd;
    int e = calculate_e(lambda);
    int d = calculate_d(lambda, e);

    printf("p, q: %lld, %lld\n", p, q);
    printf("GCD: %lld\n", gcd);
    printf("lambda: %lld\n", lambda);
    printf("e: %d\n", e);
    printf("d: %d\n", d);
    
    char* t = ASCII_val('H');
    printf("%s\n", t);

    read_msg();

    return 0;
}

int read_msg() {
    FILE *file = fopen("sample_message.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char message[100];
    char total_message[1000] = "";

    while (fgets(message, sizeof(message), file) != NULL) {
        strcat(total_message, message);
    }

    printf("Read message:\n%s\n", total_message);

    fclose(file);
    return 0;
}

char* ASCII_val(char c) {
    int asciiVal = c;
    char* str = (char*) malloc(4 * sizeof(char));

    sprintf(str, "%d", asciiVal);

    return str;
}

int find_pq(int lower, int upper) {
    int num;

    srand(time(0));

    num = (rand() % (upper - lower + 1)) + lower;

    while (isPrime(num) == false) {
        num++;
    }

    return num;
}

bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

int calculate_e(long long int lambda) {
    int e = 65537;
    while (GCD(lambda, e) != 1) {
        e++;
    }

    return e;
}

int GCD(int num1, int num2) {
    int gcd;
    int remainder;
    int numerator;
    int denominator;

    if (num1 > num2) {
        numerator = num1;
        denominator = num2;
    }

    else {
        numerator = num2;
        denominator = num1;
    }

    remainder = numerator % denominator;
    while (remainder != 0) {
        numerator = denominator;
        denominator = remainder;
        remainder = numerator % denominator;
    }

    gcd = denominator;
    return gcd;
}


int extended_euclidean(int e, int lambda, int *x, int *y) {
    if (lambda == 0) {
        *x = 1;
        *y = 0;
        return e;
    }

    int x_prev, y_prev;
    int gcd = extended_euclidean(lambda, e % lambda, &x_prev, &y_prev);

    *x = y_prev;
    *y = x_prev - (e / lambda) * y_prev;

    return gcd;
}

int calculate_d(int e, int lambda) {
    int x, y;
    int gcd = extended_euclidean(e, lambda, &x, &y);
    int d = x % lambda;

    return d < 0 ? d + lambda : d;
}