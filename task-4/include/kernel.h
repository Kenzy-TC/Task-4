extern void putInMemory(int segment, int address, char character);
extern int interrupt(int number, int AX, int BX, int CX, int DX);

void printString(const char* str);
void readString(char* buf);
void clearScreen();
void exec_command(char* input);
