#ifndef STD_LIB_H
#define STD_LIB_H

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef enum { false, true } bool;

int div(int a, int b);
int mod(int a, int b);

void memcpy(byte* src, byte* dst, unsigned int size);
unsigned int strlen(char* str);
bool strcmp(char* str1, char* str2);
void strcpy(char* src, char* dst);
void clear(byte* buf, unsigned int size);
