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
char* read_msg();
char* convert_char_to_str(char* msg);
long long int encrypt_msg(long long int m, int e, long long int n);
long long int decrypt_msg(long long int c, int d, long long int n);
int getLength(long long int num);
char* decrypt_message_to_char(long long int m);

int main()
{   
    long long int p = find_pq(100, 1000);
    long long int q = find_pq(1000, 10000);    
    long long int n = p * q;
    long long int lambda = (p-1)*(q-1);
    int e = calculate_e(lambda);
    int d = calculate_d(e, lambda);

// Converting message into ASCII values and numbers
    char* msg = read_msg();
    char* e_msg = convert_char_to_str(msg);
    long long int int_e_msg = strtoll(e_msg, NULL, 10);
    long long int c = encrypt_msg(int_e_msg, e, n);
    long long int decrypted_msg = decrypt_msg(c, d, n);
    char* actual_msg = decrypt_message_to_char(decrypted_msg);

    if (int_e_msg == decrypted_msg) {
        printf("1");
    }
    else {
        printf("0");
    }
    return 0;
}

char* read_msg() {
    FILE *file = fopen("sample_message.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return NULL;
    }

    char message[100];
    size_t total_message_size = 1000;
    char* total_message = malloc(total_message_size * sizeof(char));
    total_message[0] = '\0';

    while (fgets(message, sizeof(message), file) != NULL) {
        size_t message_length = strlen(message);
        size_t current_length = strlen(total_message);

        if (current_length + message_length >= total_message_size) {
            total_message_size *= 2;
            total_message = realloc(total_message, total_message_size * sizeof(char));
        }

        strcat(total_message, message);
    }

    fclose(file);
    return total_message;
}

char* ASCII_val(char c) {
    int asciiVal = c;
    char* str = (char*) malloc(4 * sizeof(char));
    sprintf(str, "%d", asciiVal);

    if (strlen(str) == 2) {
        str[2] = '0';
    }

    return str;
}

char* convert_char_to_str(char* msg) {
    size_t msglen = strlen(msg);
    size_t e_msg_size = 1000;
    char* e_msg = malloc(e_msg_size * sizeof(char));
    e_msg[0] = '\0';

    for (int i = 0; i < msglen; i++) {
        char* ASCII_component = ASCII_val(msg[i]);
        size_t component_len = strlen(ASCII_component);
        size_t e_msg_len = strlen(e_msg);

        if (component_len + e_msg_len >= e_msg_size) {
            e_msg_size *= 2;
            e_msg = realloc(e_msg, e_msg_size * sizeof(char));
        }

        strcat(e_msg, ASCII_component);
    }
    
    return e_msg;
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
    int e = 3;
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

long long int encrypt_msg(long long int m, int e, long long int n) {
    long long int result = 1;
    while (e > 0) {
        if (e % 2 == 1) {
            result = (result * m) % n;
        }
        m = (m * m) % n;
        e /= 2;
    }
    return result;
}

long long int decrypt_msg(long long int c, int d, long long int n) {
    long long int result = 1;
    while (d > 0) {
        if (d % 2 == 1) {
            result = (result * c) % n;
        }
        c = (c * c) % n;
        d /= 2;
    }
    return result;
}

int getLength(long long int num) {
    int length = 0;
    if (num == 0) {
        length = 1;
    } else {
        while (num != 0) {
            num /= 10;
            length++;
        }
    }
    return length;
}

char* decrypt_message_to_char(long long int m) {
    int len_m = getLength(m);
    char msg[20];
    sprintf(msg, "%lld", m);    
    char* string_msg = malloc((len_m + 1) * sizeof(char));
    string_msg[0] = '\0';
    
    int i = 0;
    while (i < len_m) {
        char first[2];
        char second[2];
        char third[2];
        strncpy(first, &msg[i], 1);
        strncpy(second, &msg[i + 1], 1);
        strncpy(third, &msg[i + 2], 1);
        first[1] = '\0';
        second[1] = '\0';
        third[1] = '\0';
        
        int bit = atoi(first) * 100 + atoi(second) * 10 + atoi(third);
        
        i += 3;

        if (bit < 320) {
            string_msg[strlen(string_msg)] = (char)bit;
        }
        else if (bit == 320) {
            string_msg[strlen(string_msg)] = ' ';
        }
        else {
            bit = bit / 10;
            string_msg[strlen(string_msg)] = (char)bit;
        }
    }
    
    return string_msg;
}
