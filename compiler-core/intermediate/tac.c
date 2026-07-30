#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple Three-Address Code (TAC) Structure for Phase 4
typedef struct {
    char op[10];
    char arg1[20];
    char arg2[20];
    char result[20];
} TACInstruction;

TACInstruction tacList[100];
int tacCount = 0;

// Function to generate and store a TAC instruction
void emit(char* op, char* arg1, char* arg2, char* result) {
    strcpy(tacList[tacCount].op, op);
    strcpy(tacList[tacCount].arg1, arg1);
    strcpy(tacList[tacCount].arg2, arg2);
    strcpy(tacList[tacCount].result, result);
    tacCount++;
}

void printTAC() {
    printf("\n--- Phase 4: Intermediate Code Generation (TAC) ---\n");
    for (int i = 0; i < tacCount; i++) {
        if (strcmp(tacList[i].op, "=") == 0) {
            printf("%s = %s\n", tacList[i].result, tacList[i].arg1);
        } else {
            printf("%s = %s %s %s\n", tacList[i].result, tacList[i].arg1, tacList[i].op, tacList[i].arg2);
        }
    }
}