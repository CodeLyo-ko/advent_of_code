#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void run(int* program, int n, long long a, long long b, long long c, int* program2, int* n2) {
    int pointer = 0;
    long long combo, lit;
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
                program2[(*n2)++] = combo % 8;
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
}


int equal(int* t1, int n1, int* t2, int n2) {
    for (int i = n2 - 1; i >= 0; i--) {
        if (t1[n1 - (n2 - i)] != t2[i]) return 0;
    }
    return 1;
}

void print_tab(int* tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d,", tab[i]);
    }
    printf("\n");
}

int hacking(int* program, int n, long long prev_a) {
    int* program2 = malloc(20 * sizeof(int));
    int n2 = 0;
    prev_a <<= 3;
    long long temp;
    for (int i = 0; i <= 7; i++) {
        n2 = 0;
        temp = prev_a | i;
            // printf("%lld\n", temp);
        run(program, n, temp, 0, 0, program2, &n2);
        if (n2 > n) return 0;
        if (equal(program, n, program2, n2)) {
            if (n == n2) {
               printf("%lld\n", temp);
        print_tab(program2, n2);
                return 1;
            }
            if(hacking(program, n, temp)) return 1;
        }
    }
}

int main() {
    long long a, b, c;

    int* program = malloc(20 * sizeof(int));
    int n = 0;

    scanf("Register A: %d\nRegister B: %d\nRegister C: %d\n\nProgram: ", &a, &b, &c);
    while(getchar() != '\n') {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%d,", &program[n++]);
    }


    hacking(program, n, 0);


    return 0;
}
