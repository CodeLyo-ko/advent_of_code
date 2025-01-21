#include <stdio.h>
#include <stdlib.h>

void make_zone(char** input, int n, int** index, int curr_index, int i, int j) {

    if(index[i][j] == curr_index) return;

    index[i][j] = curr_index;
    if ( i > 0)
        if(input[i - 1][j] == input[i][j])
            make_zone(input, n, index, curr_index, i - 1, j);
    if ( j > 0)
        if(input[i][j - 1] == input[i][j])
            make_zone(input, n, index, curr_index, i, j - 1);
    if ( i < n - 1)
        if(input[i + 1][j] == input[i][j])
            make_zone(input, n, index, curr_index, i + 1, j);
    if ( j < n - 1)
        if(input[i][j + 1] == input[i][j])
            make_zone(input, n, index, curr_index, i, j + 1);
}

int main() {
    char** input = malloc(150 * 150 * sizeof(char));
    int n = 0;
    int m = 0;

    int** index = malloc(150 * 150 * sizeof(int));

    int* area = malloc(150 * 150 * sizeof(int));
    int* perim = malloc(150 * 150 * sizeof(int));

    while(getchar() != EOF ) {
        fseek(stdin, -1, SEEK_CUR);
        input[n] = malloc(150 * sizeof(char));
        index[n] = malloc(150 * sizeof(int));
        fgets(input[n], 150, stdin);
        n++;
    }
    m = n;

    int curr_index = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (index[i][j])
                continue;
            make_zone(input, n, index, curr_index, i, j);
            curr_index++;
        }
    }

     for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //printf("%d ",  index[i][j]);
            area[index[i][j]]++;
            if (j > 0) {
                if (input[i][j - 1] != input[i][j]) {
                    perim[index[i][j]]++;
                }
            }
            else
                perim[index[i][j]]++;

            if (i > 0) {
                if (input[i - 1][j]  != input[i][j])
                    perim[index[i][j]]++;
            }
            else
                perim[index[i][j]]++;

            if (i < n - 1) {
                if (input[i + 1][j] != input[i][j]) {
                    perim[index[i][j]]++;
                }
            }
            else
                perim[index[i][j]]++;

            if (j < n - 1) {
                if (input[i][j + 1] != input[i][j]) {
                    perim[index[i][j]]++;
                }
            }
            else
                perim[index[i][j]]++;
        }
        //printf("\n");
    }

    int total = 0;
    for (int i = 1; i < curr_index; i++) {
        total += area[i] * perim[i];
        //printf("%d %d\n", area[i], perim[i]);
    }
    printf("%d\n", total);

    return 0;
}
