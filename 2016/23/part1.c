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
    jnz,
    tgl
} instr_t;

typedef enum {
    reg,
    num
} type_t;

typedef struct {
    instr_t instr;
    type_t x_type;
    type_t y_type;
    int x;
    int y;
} line_t;

line_t line_to_instr(char* line) {
    char instr_str[MAX_CHAR];
    char x[MAX_CHAR];
    char y[MAX_CHAR];

    sscanf(line, "%s %s %s\n", instr_str, x, y);
    line_t instr;
    
    if (!strcmp(instr_str, "cpy")) {
        instr.instr = cpy;
    }
    else if (!strcmp(instr_str, "inc")) {
        instr.instr = inc;
    }
    else if (!strcmp(instr_str, "dec")) {
        instr.instr = dec;
    }
    else if (!strcmp(instr_str, "jnz")) {
        instr.instr = jnz;
    }
    else if (!strcmp(instr_str, "tgl")) {
        instr.instr = tgl;
    }

    if (x[0] >= 'a' && x[0] <= 'z') {
        instr.x_type = reg;
        instr.x = x[0] - 'a';
    }
    else {
        instr.x_type = num;
        char* end;
        instr.x = strtol(x, &end, 10);
    }
    instr.y = 0;
    instr.y_type = 0;

    if (instr.instr == jnz || instr.instr == cpy) {
        if (y[0] >= 'a' && y[0] <= 'z') {
            instr.y_type = reg;
            instr.y = y[0] - 'a';
        }
        else {
            instr.y_type = num;
            char* end;
            instr.y = strtol(y, &end, 10);
        }
    }

    return instr;
}

void run_program(line_t* program, int n_program, int* registers) {
    int line = 0;


    while (line < n_program) {
        line_t instr = program[line];

        switch (instr.instr) {
            case cpy:
                if (instr.y_type == num) {
                    line++;
                    break;
                }
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
                int x, y;
                if (instr.x_type == reg) {
                    x = registers[instr.x];
                }
                else {
                    x = instr.x;
                }
                if (instr.y_type == reg) {
                    y = registers[instr.y];
                }
                else {
                    y = instr.y;
                }
                if (x == 0) {
                    line++;
                    break;
                }
                line += y;
                break;
            case tgl:
                int i = registers[instr.x] + line;
                if (i < 0 || i >= n_program) {
                    line++;
                    break;
                }
                switch (program[i].instr) {
                    case inc:
                        program[i].instr = dec;
                        break;
                    case dec:
                    case tgl:
                        program[i].instr = inc;
                        break;
                    case jnz:
                        program[i].instr = cpy;
                        break;
                    case cpy:
                        program[i].instr = jnz;
                        break;
                }
                line++;
                break;
        }
    }
}

int main() {
    int* registers = calloc(MAX_REGISTER, sizeof(int));
    registers[0] = 7;

    line_t* program = malloc(MAX_LINES * sizeof(line_t));
    int n_program = 0;

    char* line = malloc(MAX_CHAR * sizeof(char));
    while (fgets(line, MAX_CHAR, stdin)) {
        program[n_program++] = line_to_instr(line);
    }

    run_program(program, n_program, registers);
    printf("%d\n", registers[0]);

    return 0;
}
