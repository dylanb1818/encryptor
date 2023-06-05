#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int ASCII_val(char c);
int find_pq(int lower, int upper);
bool isPrime(int n);
int GCD(int num1, int num2);

int main()
{   
    long long int p = find_pq(1000000, 10000000);
    long long int q = find_pq(100000000, 1000000000);
    
    bool c = isPrime(p);
    bool d = isPrime(q);

    printf("%lld, %lld\n", p, q);
    
    long long int n = p * q;

    long long int gcd = GCD(p-1, q-1);
    printf("GCD: %lld\n", gcd);

    long long int lambda = ((p-1)*(q-1))/gcd;
    printf("lambda: %lld\n", lambda);

    return 0;
}

int ASCII_val(char c) {
    int asciiVal = c;
    asciiVal++;
    char character = (char)asciiVal;
    return character;
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