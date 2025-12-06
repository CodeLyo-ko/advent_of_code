#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ 10000

int main(){
    char** lines = malloc(MAX_ * MAX_ * sizeof(char));
    int n_lines = -1;
    
    do {
        n_lines++;
        lines[n_lines] = malloc(MAX_ * sizeof(char));
    } while (fgets(lines[n_lines], sizeof(char) * MAX_, stdin));

    char** columns = malloc(MAX_ * MAX_ * sizeof(char));
    int n_columns = strlen(lines[0]) - 1;

    for (int i = 0; i < n_columns; i++) {
        columns[i] = malloc(MAX_ * sizeof(char));
        for (int j = 0; j < n_lines; j++) {
            columns[i][j] = lines[j][i];
        }
    }

    char op = '\0';
    int k;
    long int res = 0;
    long int temp = 0;

    for (int i = 0; i < n_columns; i++) {
        if (op == '\0') {
            op = columns[i][strlen(columns[i]) - 1];
            temp = 0;
            if (op == '*') temp = 1;
        }
        if (sscanf(columns[i], "%d", &k) <= 0  ) {
            op = '\0';
            res += temp;
            continue;
        }

        if (op == '*') {
            temp *= k;
        }
        else {
            temp += k;
        }

    }

    res += temp;

    printf("%ld\n", res);

    return 0;
}
