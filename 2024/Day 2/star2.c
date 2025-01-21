#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_from_list(int* input, int n, int i, int* output) {
    int k = 0;
    for (int j = 0; j < n; j++) {
        if (j == i) continue;
        output[k++] = input[j];
    }
}
int main() {
    int* report = malloc(20 * sizeof(int));
    int* report2 = malloc(20 * sizeof(int));
    char* line = malloc(40 * sizeof(char));
    char *endptr;
    char* token;
    int n = 0;
    int safe_report = 0;
    int incr = 1;
    int is_safe = 1;
    int diff;

    while(fgets(line, 40, stdin)) {
        n = 0;
        is_safe = 1;
        token = strtok(line, " \n");
        report[n] = (int)strtol(token, &endptr, 10);
        n++;

        while ((token = strtok(NULL, " \n")) != NULL){
            report[n] = (int)strtol(token, &endptr, 10);
            n++;
        }

        for (int j = 0; j < n; j++) {
            is_safe = 1;
            remove_from_list(report, n, j, report2);

            for (int k = 0; k < n - 1; k++){
                printf("%d ", report2[k]);
            }
            printf("\n");

            incr = report2[1]>report2[0]?1:-1;

            for (int i = 0; i < n - 2; i++){

                diff = (report2[i+1] - report2[i]) * incr;

                if (diff < 1 || diff > 3) {
                    is_safe = 0;
                    printf("%d\n", diff);
                    break;
                }
            }
            if (is_safe) {
                printf("a\n");
                safe_report++;
                break;
            }
        }
    }

    printf("%d\n", safe_report);

    return 0;
}
