#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int* report = malloc(20 * sizeof(int));
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

        incr = report[1]>report[0]?1:-1;
        printf("%d\n", incr);

        for (int i = 0; i < n - 1; i++){

            diff = (report[i+1] - report[i]) * incr;


            printf("diff %d\n", diff);

            if (diff < 1 || diff > 3) {
                is_safe = 0;
                break;
            }
        }
        if (is_safe) {
            safe_report++;
        }


    }

    printf("%d\n", safe_report);

    return 0;
}
