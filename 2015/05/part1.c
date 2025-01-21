#include <stdio.h>
#include <stdlib.h>

int contains_3_vowels(char* string, int n) {
    int vowel = 0;
    for (int i = 0; i < n; i++) {
        if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u') {
            vowel++;
        }
    }
    return vowel >= 3;
}

int contains_doubled_letter(char* string, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (string[i] == string[i + 1]) return 1;
    }
    return 0;
}

int not_contains_forbidden(char* string, int n) {
    for (int i = 0; i < n - 1; i++) {
        if ((string[i] == 'a' && string[i + 1] == 'b') || (string[i] == 'c' && string[i + 1] == 'd') || (string[i] == 'p' && string[i + 1] == 'q') || (string[i] == 'x' && string[i + 1] == 'y') ) {
            return 0;
        }
    }
    return 1;
}

int is_nice(char* string, int n) {
    return (contains_3_vowels(string, n) && contains_doubled_letter(string, n) && not_contains_forbidden(string, n));
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
