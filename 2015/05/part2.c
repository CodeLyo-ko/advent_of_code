#include <stdio.h>
#include <stdlib.h>

int contains_pair(char* string, int n) {
    for (int i = 0; i < n - 3; i++) {
        for (int j = i + 2; j < n - 1; j++) {
            if (string[i] == string[j] && string[i + 1] == string[j + 1])
                return 1;
        }
    }
    return 0;
}

int contains_repeat(char* string, int n) {
    for (int i = 0; i < n - 2; i++) {
        if (string[i] == string[i + 2])
            return 1;
    }
    return 0;
}

int is_nice(char* string, int n) {
    return (contains_pair(string, n) && contains_repeat(string, n));
}

int main() {
    char* string = malloc(20 * sizeof(char));
    int n = 0;

    int total = 0;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        n = 0;
        while((string[n++] = getchar()) != '\n');
        string[--n] = '\0';

        total += is_nice(string, n);

    }
    printf("%d\n", total);
}
