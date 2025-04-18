#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    HLF,
    TPL,
    INC,
    JMP,
    JIE,
    JIO
} instruction_t;

typedef enum {
    A,
    B
} reg_t;

typedef struct {
    instruction_t instruction;
    reg_t reg;
    int offset;
} command_t;

void parse_command (command_t* command, char* line) {
    if (!strncmp(line, "hlf", 3)) {
        command->instruction = HLF;
    }
    else if (!strncmp(line, "tpl", 3)) {
        command->instruction = TPL;
    }
    else if (!strncmp(line, "inc", 3)) {
        command->instruction = INC;
    }
    else if (!strncmp(line, "jmp", 3)) {
        command->instruction = JMP;
    }
    else if (!strncmp(line, "jie", 3)) {
        command->instruction = JIE;
    }
    else if (!strncmp(line, "jio", 3)) {
        command->instruction = JIO;
    }

    if (command->instruction != JMP) {
        switch (line[4]) {
            case 'a': 
                command->reg = A;
                break;
            case 'b':
                command->reg = B;
                break;
        }
    }

    command->offset = 1;
    if (command->instruction == JMP) {
        command->offset = strtol(&line[4], NULL, 10);
    }
    else if (command->instruction == JIE || command->instruction == JIO) {
        command->offset = strtol(&line[7], NULL, 10);
    }
}

void execute_program(command_t* program, int n, long* a, long* b) {
    int i = 0;
    long* reg;
    while (i < n) {
        if (program[i].instruction == JMP) {
            i += program[i].offset;
            continue;
        }

        switch (program[i].reg) {
            case A:
                reg = a;
                break;
            case B:
                reg = b;
                break;
        }

        switch (program[i].instruction) {
            case HLF:
                *reg /= 2;
                i++;
                break;
            case TPL:
                *reg *= 3;
                i++;
                break;
            case INC:
                (*reg)++;
                i++;
                break;
            case JIE:
                if ((*reg)%2 == 0){
                    i += program[i].offset;
                }
                else {
                    i++;
                }
                break;
            case JIO:
                if ((*reg) == 1){
                    i += program[i].offset;
                }
                else {
                    i++;
                }
                break;
        }
    }
}

int main() {
    long a = 0;
    long b = 0;
    
    command_t* program = malloc(500 * sizeof(command_t));
    int n_command = 0;

    char* line = malloc(500 * sizeof(char));
    while (fgets(line, 500, stdin)) {
        parse_command(&program[n_command], line);
        n_command++;
    }

    execute_program(program, n_command, &a, &b);

    printf("%ld\n", b);
    return 0;
}
