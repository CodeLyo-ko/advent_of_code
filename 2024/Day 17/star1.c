#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int a, b, c;

    int* program = malloc(20 * sizeof(int));
    int n = 0;

    scanf("Register A: %d\nRegister B: %d\nRegister C: %d\n\nProgram: ", &a, &b, &c);
    while(getchar() != '\n') {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%d,", &program[n++]);
    }

    int pointer = 0;
    int combo, lit;
    while (pointer < n) {
        switch (program[pointer + 1]) {
            case 4:
                combo = a;
                break;
            case 5:
                combo = b;
                break;
            case 6:
                combo = c;
                break;
            default:
                combo = program[pointer + 1];
                break;
        }
        lit = program[pointer + 1];

        switch (program[pointer]) {
            case 0:
                a /= (pow(2, combo));
                break;
            case 1:
                b ^= lit;
                break;
            case 2:
                b = combo % 8;
                break;
            case 3:
                if (a) {
                    pointer = lit - 2;
                }
                break;
            case 4:
                b ^= c;
                break;
            case 5:
                printf("%d,", combo % 8);
                break;
            case 6:
                b = a / (pow(2, combo));
                break;
            case 7:
                c = a / (pow(2, combo));
                break;
        }
        pointer += 2;
    }

    return 0;
}
