#include <stdio.h>
#include <stdlib.h>

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

    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            total += (input[i][j] == 'A' && ((input[i-1][j-1] == 'S' && input[i+1][j+1] == 'M') || (input[i-1][j-1] == 'M' && input[i+1][j+1] == 'S')) && ((input[i-1][j+1] == 'S' && input[i+1][j-1] == 'M') || (input[i-1][j+1] == 'M' && input[i+1][j-1] == 'S')));
        }
    }

    printf("%d\n", total);


    return 0;
}
