#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ASCII_val(char c);

int main()
{
    FILE* ptr;
    char ch;

    ptr = fopen("sample_message.txt", "r");

    if (NULL == ptr) {
        printf("file can't be opened \n");
    }

    printf("content of this file are \n");

    while ((ch = fgetc(ptr)) != EOF) {
        printf("%c\n", ch);
        char a = ASCII_val(ch);
        printf("%c\n", a);
        printf("-------\n");
    }

    fclose(ptr);
    return 0;
}

int ASCII_val(char c) {
    // printf("ASCII Value of %c = %d \n", c, c);
    int asciiVal = c;
    asciiVal++;

    char character = (char)asciiVal;

    return character;
}


// Did this change anything?