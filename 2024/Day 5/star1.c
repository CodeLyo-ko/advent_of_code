#include <stdio.h>
#include <stdlib.h>

int main() {
    int** rules = malloc(1200 * 2 * sizeof(int));
    int n_rules = 0;

    do {
        rules[n_rules] = malloc(2 * sizeof(int));
    } while (scanf("%d|%d", &rules[n_rules++][0], &rules[n_rules][1]) == 2);

    n_rules--;

    int* update = malloc(50 * sizeof(int));
    int n_update = 0;

    int wrong = 0;

    int tot = 0;

    getchar();

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        n_update = 0;
        while(getchar() != '\n') {
            if (n_update == 0) fseek(stdin, -1, SEEK_CUR);
            scanf("%d", &update[n_update++]);
        }
        wrong = 0;
        for (int i = 0; i < n_update - 1; i++) {
            for (int j = i + 1; j < n_update; j++) {
                for (int k = 0; k < n_rules; k++) {
                    if (rules[k][0] == update[j] && rules[k][1] == update[i]){
                        wrong = 1;
                        break;
                    }
                }
                if (wrong) break;
            }
            if (wrong) break;
        }


        if (!wrong) {
            tot += update[(n_update / 2)];
        }
    }

    printf("%d\n", tot);


    return 0;
}
