#include <stdio.h>
#include <stdlib.h>

int check_line(char** input, int i, int j) {
    if ((input[i][j] == 'X' && input[i][j+1] == 'M' && input[i][j+2] == 'A' && input[i][j+3] == 'S') || (input[i][j] == 'S' && input[i][j+1] == 'A' && input[i][j+2] == 'M' && input[i][j+3] == 'X')) {
        return 1;
    }
    return 0;
}

int check_column(char** input, int i, int j) {
    if ((input[i][j] == 'X' && input[i+1][j] == 'M' && input[i+2][j] == 'A' && input[i+3][j] == 'S') || (input[i][j] == 'S' && input[i+1][j] == 'A' && input[i+2][j] == 'M' && input[i+3][j] == 'X')) {
        return 1;
    }
    return 0;
}

int check_diag(char** input, int i, int j) {
    if ((input[i][j] == 'X' && input[i+1][j+1] == 'M' && input[i+2][j+2] == 'A' && input[i+3][j+3] == 'S') || (input[i][j] == 'S' && input[i+1][j+1] == 'A' && input[i+2][j+2] == 'M' && input[i+3][j+3] == 'X')) {
        return 1;
    }
    return 0;
}

int check_diag2(char** input, int i, int j){
    if ((input[i][j] == 'X' && input[i+1][j-1] == 'M' && input[i+2][j-2] == 'A' && input[i+3][j-3] == 'S') || (input[i][j] == 'S' && input[i+1][j-1] == 'A' && input[i+2][j-2] == 'M' && input[i+3][j-3] == 'X')) {
            return 1;
        }
        return 0;
}

int main() {
    char** input = malloc(1000 * 1000 * sizeof(char) );
    int n = 0;
    int m = 0;

    int total = 0;

    input[0] = malloc(1000 * sizeof(char));
    while ((input[n][0] = getchar()) != EOF) {
        m = 1;
        while ((input[n][m++] = getchar()) != '\n') {
        }
        input[n][m - 1] = '\0';
        n++;
        input[n] = malloc(1000 * sizeof(char));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(j < m - 3)
            total += check_line(input, i, j);
            if (i < n - 3)
            total += check_column(input, i, j);
            if (i < n - 3 && j < n - 3 )
            total += check_diag(input, i, j);
            if (i < n - 3 && j > 2)
            total += check_diag2(input, i, j);
        }
    }

    printf("%d\n", total);


    return 0;
}
