#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10000

int main() {
    int* row = malloc(MAX_ * sizeof(int));
    int n = 0;
    int res = 0;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        n = 0;
        while (getchar() != '\n') {
            fseek(stdin, -1, SEEK_CUR);
            scanf("%d", &row[n++]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (row[i] % row[j] == 0) {
                    res += row[i] / row[j];
                }
            }
        }
    }

    printf("%d\n", res);

    return 0;
}
