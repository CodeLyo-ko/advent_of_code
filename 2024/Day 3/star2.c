#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int str_to_int (char* string, int n) {
    int tot = 0;
    int pow_ten = 1;
    for (int i = n - 1; i >= 0; i--) {
        tot += (string[i] - '0') * pow_ten;
        pow_ten *= 10;
    }
    return tot;
}

int main() {
    char* input = malloc(20000 * sizeof(char));
    char* int1_str = malloc(5 * sizeof(char));
    int int1_n;
    int int1;
    char* int2_str = malloc(5 * sizeof(char));
    int int2_n;
    int int2;
    int j;
    int total = 0;
    int enabled = 1;

    fgets(input, 20000, stdin);

    for (int i = 0; input[i] != '\0'; i++) {
        if (enabled && input[i] == 'm' && input[i+1] == 'u' && input[i+2] == 'l' && input[i+3] == '(') {
            int1_n = 0;
            for (j = i + 4; isdigit(input[j]); j++) {
                int1_str[int1_n++] = input[j];
            }
            if (input[j] == ',') {
                int1 = str_to_int(int1_str, int1_n);
                int2_n = 0;
                for (j += 1; isdigit(input[j]); j++) {
                    int2_str[int2_n++] = input[j];
                }
                if (input[j] == ')') {
                    int2 = str_to_int(int2_str, int2_n);
                    total += int1 * int2;
                }
            }
        }
        else if (input[i] == 'd' && input[i+1] == 'o' && input[i+2] == '(' && input[i+3] == ')'){
            enabled = 1;
        }
        else if (input[i] == 'd' && input[i+1] == 'o' && input[i+2] == 'n' && input[i+3] == '\'' && input[i+4] == 't' && input[i+5] == '(' && input[i+6] == ')') {
            enabled = 0;
        }
    }

        printf("%d\n", total);
    return 0;
}
