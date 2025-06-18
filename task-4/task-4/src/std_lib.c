#include "std_lib.h"

int div(int a, int b) {
    int result = 0;
    while (a >= b) {
        a -= b;
        result++;
    }
    return result;
}


int mod(int a, int b) {
    while (a >= b) {
        a -= b;
    }
    return a;
}

void memcpy(byte* src, byte* dst, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        dst[i] = src[i];
    }
}

unsigned int strlen(char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

bool strcmp(char* str1, char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return false;
        }
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

void strcpy(char* src, char* dst) {
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
}

void clear(byte* buf, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        buf[i] = 0;
    }
}
