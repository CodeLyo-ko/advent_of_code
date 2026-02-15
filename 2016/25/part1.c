#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_CHAR 100
#define MAX_REGISTER 5
#define MAX_RUN 100000000

typedef enum {
    cpy,
    inc,
    dec,
    jnz,
    out
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
    else if (!strcmp(instr_str, "out")) {
        instr.instr = out;
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

int run_program(line_t* program, int n_program, int* registers) {
    int line = 0;
    int k = 0;
    int prev = 1;
    int x, y, i;
    
    int r = 0;
    while (line < n_program && r < MAX_RUN) {
        r++;
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
            case out:
                if (instr.x_type == reg) {
                    x = registers[instr.x];
                }
                else {
                    x = instr.x;
                }
                k = x;
                
                if (k == prev) {
                    return 0;
                }
                prev = k;
                line++;
                break;
        }
    }
    return 1;
}

int main() {
    int* registers = calloc(MAX_REGISTER, sizeof(int));

    line_t* program = malloc(MAX_LINES * sizeof(line_t));
    int n_program = 0;

    char* line = malloc(MAX_CHAR * sizeof(char));
    while (fgets(line, MAX_CHAR, stdin)) {
        program[n_program++] = line_to_instr(line);
    }

    for (int a = 0; 1; a++) {
        for (int i = 0; i < MAX_REGISTER; i++) {
            registers[i] = 0;
        }
        registers[0] = a;
        int res = run_program(program, n_program, registers);
        if (res) {
            printf("%d\n", a);
            break;
        }

    }

    return 0;
}
