#include "std_lib.h"
#include "kernel.h"

// Masukkan variabel global dan prototipe fungsi di sini

int main() {
    char buf[128];

    clearScreen();
    printString("LilHabOS - D02\n");

    while (true) {
        printString("$> ");
        readString(buf);
        printString("\n");

        if (strlen(buf) > 0) {
            printString("$> ");
            readString(buf);
            exec_comand(buf);
        }
    }
}

// Masukkan fungsi di sini
void printString(const char* str) {
    while (*str != '\0') {
        __asm__ __volatile__ (
            "int $0x10"
            : 
            : "a" (0x0E00 | *str), "b" (0x0007)
        );
        str++;
    }
}

void readString(char* buf) {
    int idx = 0;
    char key;

    while (true) {
        __asm__ __volatile__ (
            "int $0x16"
            : "=a" (key)
            : "a" (0x0000)
        );

        switch (key) {
            case 0x08:
                if (idx > 0) {
                    idx--;
                    printString("\b \b");
                }
                break;

            case 0x0D:
                buf[idx] = '\0';
                return;

            default:
                if (idx < 127 && key >= 32 && key <= 126) {
                    buf[idx++] = key;
                    printString(&key);
                }
                break;
        }
    }
}

void clearScreen() {
     __asm__ __volatile__ (
        "int $0x10"
        : 
        : "a" (0x0600), "b" (0x07), "c" (0x0000), "d" (0x184F)
    );

    __asm__ __volatile__ (
        "int $0x10"
        : 
        : "a" (0x0200), "b" (0x00), "d" (0x0000)
    );
}
void echo(char* args){
	printString(args);
	printString("\n");
}

void grep(const char* pattern, const char* text) {
    int found = 0;
    char* line_start = (char*)text;
    
    while (*text) {
        if (*text == '\n' || *(text+1) == '\0') {
            char saved_char = *(text + 1) == '\0' ? *++text : *text;
            *text = '\0';
            
            if (strstr(line_start, pattern)) {
                printString(line_start);
                printString("\n");
                found = 1;
            }
            
            *text = saved_char;
            line_start = text + 1;
        }
        text++;
    }
    
    if (!found) printString("NULL\n");
}
void wc(const char* text) {
    int lines = 0, words = 0, chars = 0;
    bool in_word = false;

    while (*text) {
        chars++;
        
        if (*text == '\n') lines++;
        if (*text == ' ' || *text == '\n' || *text == '\t') {
            in_word = false;
        } else if (!in_word) {
            words++;
            in_word = true;
        }
        text++;
    }

    char output[32];
    strcpy(itoa(lines), output);
    strcat(output, " ");
    strcat(output, itoa(words));
    strcat(output, " ");
    strcat(output, itoa(chars));
    strcat(output, "\n");
    
    printString(output);
}

void exec_command(char* input) {
    char* pipe = strchr(input, '|');
    if (!pipe) {
        if (strcmp(input, "clear") == 0) {
            clearScreen();
        } else {
            printString("Unknown command\n");
        }
        return;
    }

    *pipe++ = '\0';
    char* cmd1 = input;
    char* cmd2 = pipe;

    while (*cmd1 == ' ') cmd1++;
    while (*cmd2 == ' ') cmd2++;

    if (strstr(cmd1, "echo ") == cmd1) {
        char* text = cmd1 + 5;
        if (strstr(cmd2, "grep ") == cmd2) {
            grep(cmd2 + 5, text);
        } else if (strcmp(cmd2, "wc") == 0) {
            wc(text);
        } else {
            printString("Invalid command\n");
        }
    } else {
        printString("First command must be echo\n");
    }
}

