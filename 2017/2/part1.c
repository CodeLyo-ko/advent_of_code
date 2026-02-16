#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10000

int main() {
    int* row = malloc(MAX_ * sizeof(int));
    int n = 0;
    int min, max;
    int res = 0;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        n = 0;
        while (getchar() != '\n') {
            fseek(stdin, -1, SEEK_CUR);
            scanf("%d", &row[n++]);
        }
        min = row[0];
        max = row[0];
        for (int i = 0; i < n; i++) {
            if (row[i] < min) min = row[i];
            if (row[i] > max) max = row[i];
        }
        res += max - min;
    }

    printf("%d\n", res);

    return 0;
}
