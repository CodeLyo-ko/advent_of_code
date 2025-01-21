#include <stdio.h>
#include <stdlib.h>

int main() {
    int* line = malloc(100000 * sizeof(int));
    int n = 0;

    int* line_file = malloc(1000000 * sizeof(int));
    int m = 0;

    char c;

    while ((c = getchar()) != '\n') {
        line[n++] = c - '0';
    }

    long long total = 0;

    for (int i = 0; i < n; i++) {
        if (i%2 == 0) {
            while (line[i] > 0) {
                line_file[m] = i / 2;
                line[i]--;
                m++;
            }
        }
        else {
            while (line[i] > 0) {
                line_file[m] = -1;
                line[i]--;
                m++;
            }
        }
    }

    int i = m - 1;
    int j;

    int i_space;
    int j_space;

    while (i > 0) {
        if (line_file[i] == -1) {
            i--;
            continue;
        }

        j = i - 1;
        while (j > 0 && line_file[j] == line_file[i]) {
            j--;
        }
        j++;

        i_space = 0;
        while (1) {
            while (line_file[i_space] != -1 && i_space < j) {
                i_space++;
            }

            if (i_space == j) {
                break;
            }

            j_space =  i_space;
            while (line_file[j_space] == -1 && j_space < j && (j_space - i_space) < (i - j)) {
                j_space++;
            }

            if (line_file[j_space] == -1 && j_space < j) {
                for (int a = i_space; a <= j_space; a++) {
                line_file[a] = line_file[i];
                }
                for (int a = j; a <= i; a++) {
                    line_file[a] = -1;
                }
                break;
            }

            i_space = j_space;

        }

        i = j - 1;
    }

    for (int a = 0; a < m; a++) {
        if (line_file[a] == -1) {
            continue;
        }
        total += a * line_file[a];
    }


    printf("%lld\n", total);

    return 0;
}
