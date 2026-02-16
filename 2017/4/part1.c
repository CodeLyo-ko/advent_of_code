#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ 10000

int is_valid(char** line, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!strcmp(line[i], line[j])) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    char** line = malloc(MAX_ * MAX_ * sizeof(char));
    int n = 0;
    for (int i = 0; i < MAX_; i++) {
        line[i] = malloc(MAX_ * sizeof(char));
    }

    int res = 0;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        n = 0;
        while(getchar() != '\n') {
            fseek(stdin, -1, SEEK_CUR);
            scanf("%s", line[n++]);
        }

        res += is_valid(line, n);
    }

    printf("%d\n", res); 

    return 0;
}
