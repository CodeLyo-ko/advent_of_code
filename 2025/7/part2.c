#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10000

int main() {
    long int** grid = malloc(MAX_ * MAX_ * sizeof(long int));
    int n = 0;
    int m = 0;


    char c;
    while((c = getchar()) != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        grid[n] = malloc(MAX_ * sizeof(long int));

        m = 0;
        while((c = getchar()) != '\n'){
            if (c == 'S') {
                grid[n][m] = 1;
            }
            else if (c == '.') {
                grid[n][m] = 0;
            }
            else {
                grid[n][m] = -1;
            }
            m++;
        }
        n++;
    }

    long int res = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if ( grid[i][j] > 0) {
                if (grid[i+1][j] >= 0){
                    grid[i+1][j] += grid[i][j];
                }
                else if (grid[i+1][j] == -1) {
                    grid[i+1][j - 1] += grid[i][j];
                    grid[i+1][j + 1] += grid[i][j];
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        res += grid[n - 1][i];
    }
    printf("%ld\n", res);

    return 0;
}
