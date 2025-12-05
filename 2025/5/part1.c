#include <stdio.h>
#include <stdlib.h>
#define MAX_ 5000

int main(){
    long int** fresh = malloc(2 * MAX_ * sizeof(long int));
    int n_f = 0;

    long int res = 0;
    char buffer[MAX_];

    while(getchar() != '\n') {
        fseek(stdin, -1, SEEK_CUR);

        fresh[n_f] = malloc(2 * sizeof(int));
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%ld-%ld", &fresh[n_f][0], &fresh[n_f][1]);
        n_f++;
    }

    long int id;
    while (scanf("%ld\n", &id) > 0) {
        for (int i = 0; i < n_f; i++) {
            if (id >= fresh[i][0] && id <= fresh[i][1]) {
                res++;
                break;
            }
        }
    }

    printf("%ld\n", res);

    return 0;
}
