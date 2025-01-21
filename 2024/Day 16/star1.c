#include <stdio.h>
#include <stdlib.h>

int main() {
   char** map = malloc(200 * 200 * sizeof(char));
   int n = 0;
   int m = 0;

   int** min = malloc(200 * 200 * sizeof(int));
   char** dir = malloc(200 * 200 * sizeof(char));

   while(getchar() != EOF) {
       fseek(stdin, -1, SEEK_CUR);
       map[n] = malloc(200 * sizeof(char));
       min[n] = malloc(200 * sizeof(int));
       dir[n] = malloc(200 * sizeof(char));
       fgets(map[n], 200, stdin);
       n++;
    }
    for (m = 0; map[0][m] != '\n'; m++);

    int x, y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            min[i][j] = -1;
            if (map[i][j] == 'S') {
                min[i][j] = 0;
                dir[i][j] = 'E';
            }
            else if (map[i][j] == 'E') {
                x = i;
                y = j;
            }
        }
    }

    int stop = 0;
    int temp;

    while(!stop) {
        stop = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (map[i][j] == '#') continue;
                if (min[i - 1][j] != -1 && dir[i - 1][j] != 'N') {
                    temp = 1 + min[i - 1][j];
                    if (dir[i - 1][j] != 'S') {
                        temp += 1000;
                    }
                    if (min[i][j] == -1 || temp < min[i][j]) {
                        stop = 0;
                        min[i][j] = temp;
                        dir[i][j] = 'S';
                    }
                }
                if (min[i + 1][j] != -1 && dir[i + 1][j] != 'S') {
                    temp = 1 + min[i + 1][j];
                    if (dir[i + 1][j] != 'N') {
                        temp += 1000;
                    }
                    if (min[i][j] == -1 || temp < min[i][j]) {
                        stop = 0;
                        min[i][j] = temp;
                        dir[i][j] = 'N';
                    }
                }
                if (min[i][j - 1] != -1 && dir[i][j - 1] != 'O') {
                    temp = 1 + min[i][j - 1];
                    if (dir[i][j - 1] != 'E') {
                        temp += 1000;
                    }
                    if (min[i][j] == -1 || temp < min[i][j]) {
                        stop = 0;
                        min[i][j] = temp;
                        dir[i][j] = 'E';
                    }
                }
                if (min[i][j + 1] != -1 && dir[i][j + 1] != 'E') {
                    temp = 1 + min[i][j + 1];
                    if (dir[i][j + 1] != 'O') {
                        temp += 1000;
                    }
                    if (min[i][j] == -1 || temp < min[i][j]) {
                        stop = 0;
                        min[i][j] = temp;
                        dir[i][j] = 'O';
                    }
                }
            }
        }
    }

    printf("%d\n", min[x][y]);
    return 0;
}
