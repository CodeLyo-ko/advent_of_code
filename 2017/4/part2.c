#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ 10000

int is_anagram(char* w1, char* w2) {
    int* a1 = calloc(26, sizeof(int));
    int* a2 = calloc(26, sizeof(int));

    int n1 = strlen(w1);
    int n2 = strlen(w2);
    for (int i = 0; i < n1; i++) {
        a1[w1[i] - 'a']++;
    }
    for (int i = 0; i < n2; i++) {
        a2[w2[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (a1[i] != a2[i]) {
            free(a1);
            free(a2);
            return 0;
        }
    }
    free(a1);
    free(a2);
    return 1;
}

int is_valid(char** line, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (is_anagram(line[i], line[j])) {
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
