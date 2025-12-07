#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10000

int main() {
    char** grid = malloc(MAX_ * MAX_ * sizeof(char));
    int n = 0;
    int m = 0;


    char c;
    while((c = getchar()) != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        grid[n] = malloc(MAX_ * sizeof(char));

        m = 0;
        while((c = getchar()) != '\n'){
            if (c == 'S') c = '|';
            grid[n][m] = c;
            m++;
        }
        n++;
    }

    int res = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if ( grid[i][j] == '|') {
                if (grid[i+1][j] == '.'){
                    grid[i+1][j] = '|';
                }
                else if (grid[i+1][j] == '^') {
                    res++;
                    grid[i+1][j - 1] = '|';
                    grid[i+1][j + 1] = '|';
                }
            }
        }
    }
    printf("%d\n", res);

    return 0;
}
