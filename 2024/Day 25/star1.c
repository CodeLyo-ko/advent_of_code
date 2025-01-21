#include <stdio.h>
#include <stdlib.h>
#define N 7
#define M 5

int main() {
    char** cur =malloc(6 * 7 * sizeof(char));

    int** keys = malloc(200 * 5 * sizeof(int));
    int n_keys = 0;

    int** locks = malloc(200 * 5 * sizeof(int));
    int n_locks = 0;

    int height = 0;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        for (int i = 0; i < N; i++) {
            cur[i] = malloc(6 * sizeof(char));
            fgets(cur[i], 6, stdin);
            getchar();
        }
        getchar();

        if (cur[0][0] == '#') {
            locks[n_locks] = malloc(5 * sizeof(int));
            for (int j = 0; j < M; j++) {
                height = 0;
                for (int i = 1; i < N; i++) {
                    height += (cur[i][j] == '#');
                }
                locks[n_locks][j] = height;
            }
            n_locks++;
        }
        else {
            keys[n_keys] = malloc(5 * sizeof(int));
            for (int j = 0; j < M; j++) {
                height = 0;
                for (int i = 1; i < N - 1; i++) {
                    height += (cur[i][j] == '#');
                }
                keys[n_keys][j] = height;
            }
            n_keys++;
        }
    }

    for (int k = 0; k < n_locks; k++) {
        for (int i = 0; i < M; i++) {
            printf("%d ", locks[k][i]);
        }
        printf("\n");
    }

    for (int k = 0; k < n_keys; k++) {
        for (int i = 0; i < M; i++) {
            printf("%d ", keys[k][i]);
        }
        printf("\n");
    }

    int total = n_keys * n_locks;
    for (int k = 0; k < n_keys; k++) {
        for (int l = 0; l < n_locks; l++) {
            for (int i = 0; i < M; i++) {
                if (locks[l][i] + keys[k][i] > N - 2) {
                    total--;
                    break;
                }
            }
        }
    }

    printf("%d\n", total);

    return 0;
}
