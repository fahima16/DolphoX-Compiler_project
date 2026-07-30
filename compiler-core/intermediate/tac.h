#ifndef TAC_H
#define TAC_H

typedef struct {
    char op[10];
    char arg1[20];
    char arg2[20];
    char result[20];
} TACInstruction;

extern TACInstruction tacList[100];
extern int tacCount;

void emit(char* op, char* arg1, char* arg2, char* result);
void printTAC();

#endif