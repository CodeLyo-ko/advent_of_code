#include <stdio.h>
#include <stdlib.h>

void correct(int** rules, int n_rules, int* update, int n_update, int* corrected, int* n_corrected, int i, int j) {
    //printf("%d %d\n", i, j);
    //printf("%d %d\n", update[i], update[j]);
    if (*n_corrected == -1) return;
    if (update[j] == -1)
        correct(rules, n_rules, update, n_update, corrected, n_corrected, i, j+1);
    if (update[i] == -1) return;
    if (j >= n_update) {
        //printf("oui %d\n", update[i]);
        corrected[(*n_corrected)--] = update[i];
        //printf("%d\n", corrected[(*n_corrected)+1]);
        update[i] = -1;
        return;
    }
    for (int k = 0; k < n_rules; k++) {

        if (rules[k][0] == update[i] && rules[k][1] == update[j]){
            //printf("second");
            correct(rules, n_rules, update, n_update, corrected, n_corrected, j, j+1);
            //correct(rules, n_rules, update, n_update, corrected, n_corrected, i, j+1);
        }
    }

    correct(rules, n_rules, update, n_update, corrected, n_corrected, i, j+1);
}

int main() {
    int** rules = malloc(1200 * 2 * sizeof(int));
    int n_rules = 0;

    do {
        rules[n_rules] = malloc(2 * sizeof(int));
    } while (scanf("%d|%d", &rules[n_rules++][0], &rules[n_rules][1]) == 2);

    n_rules--;

    int* update = malloc(50 * sizeof(int));
    int n_update = 0;

    int* update_corrected = malloc(50 * sizeof(int));

    int wrong = 0;
    int n_corrected;
    int tot = 0;

    int n =0;

    getchar();

    while(getchar() != EOF) {
        n++;
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


        if (wrong) {
            printf("%d \n", n);
            for (int i =  0; i < n_update; i++) {
                printf("%d ", update[i]);
            }
            printf("\n");
            n_corrected = n_update - 1;
            for (int i = 0; i < n_update; i++) {
                correct(rules, n_rules, update, n_update, update_corrected, &n_corrected, i, i+1);

            }
            for (int i =  0; i < n_update; i++) {
                printf("%d ", update_corrected[i]);
            }
            printf("\n");
            tot += update_corrected[n_update / 2];
        }
    }

    printf("%d\n", tot);


    return 0;
}
