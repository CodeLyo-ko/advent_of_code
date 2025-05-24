#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_CHAR 100
#define MAX_REGISTER 5

typedef enum {
    cpy,
    inc,
    dec,
    jnz
} instr_t;

typedef enum {
    reg,
    num
} type_t;

typedef struct {
    instr_t instr;
    type_t x_type;
    int x;
    int y;
} line_t;

line_t line_to_instr(char* line) {
    line_t instr;
    
    if (!strncmp(line, "cpy", 3)) {
        instr.instr = cpy;
    }
    else if (!strncmp(line, "inc", 3)) {
        instr.instr = inc;
    }
    else if (!strncmp(line, "dec", 3)) {
        instr.instr = dec;
    }
    else if (!strncmp(line, "jnz", 3)) {
        instr.instr = jnz;
    }

    int offset = 4;
    int value;
    char *endptr;
    value = strtol(line + offset, &endptr, 10);
    if (endptr == line + offset) {
        instr.x_type = reg;
        instr.x = (line+offset)[0] - 'a';
        offset += 2;
    }
    else {
        instr.x_type = num;
        instr.x = value;
        offset = endptr - line + 1;
    }

    if (instr.instr == cpy) {
        instr.y = (line+offset)[0] - 'a';
    }
    else if (instr.instr == jnz) {
        value = strtol(line + offset, NULL, 10);
        instr.y = value;
    }

    return instr;
}

void run_program(line_t* program, int n_program, int* registers) {
    int line = 0;

    while (line < n_program) {
        line_t instr = program[line];
        switch (instr.instr) {
            case cpy:
                if (instr.x_type == reg) {
                    registers[instr.y] = registers[instr.x];
                }
                else {
                    registers[instr.y] = instr.x;
                }
                line++;
                break;
            case inc:
                registers[instr.x]++;
                line++;
                break;
            case dec:
                registers[instr.x]--;
                line++;
                break;
            case jnz:
                if (instr.x_type == reg) {
                    if (registers[instr.x] == 0) {
                        line++;
                        break;
                    }
                    line += instr.y;
                    break;
                }
                if (instr.x == 0) {
                    line++;
                    break;
                }
                line += instr.y;
                break;
        }
    }
}

int main() {
    int* registers = calloc(MAX_REGISTER, sizeof(int));

    line_t* program = malloc(MAX_LINES * sizeof(instr_t));
    int n_program = 0;

    char* line = malloc(MAX_CHAR * sizeof(char));
    while (fgets(line, MAX_CHAR, stdin)) {
        program[n_program++] = line_to_instr(line);
    }

    run_program(program, n_program, registers);
    printf("%d\n", registers[0]);

    return 0;
}
