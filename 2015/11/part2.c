#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void increment(char* password, int n) {
    if (n == -1) return;
    password[n]++;
    if (password[n] == 'z' + 1) {
        password[n] = 'a';
        increment(password, n-1);
    }
}

int increasing_3_letters(char* password, int n) {
    for (int i = 0; i < n - 2; i++) {
        if (password[i] == password[i + 1] - 1 && password[i + 1] == password[i + 2] - 1 ) {
            return 1;
        }
    }
    return 0;
}

int letters_forbidden(char* password, int n) {
    for (int i = 0; i < n; i++) {
        if (password[i] == 'i' || password[i] == 'o' || password[i] == 'l')
            return 0;
    }
    return 1;
}

int pairs_letters(char* password, int n) {
    int pairs = 0;
    char pair_1;

    for (int i = 0; i < n - 1; i++) {
        if (password[i] == password[i + 1]) {
            if (pairs) {
                if (pair_1 == password[i]) {
                    continue;
                }
                return 1;
            }

            pairs = 1;
            pair_1 = password[i];
        }
    }

    return 0;
}

int is_good(char* password, int n) {
    return increasing_3_letters(password, n) && letters_forbidden(password, n) && pairs_letters(password, n);
}

int main() {
    char* password;
    strcpy(password, "vzbxxyzz");
    int n = 8;


    do {
        increment(password, strlen(password) - 1);
    } while (!is_good(password, strlen(password)));

    printf("%s\n", password);
    return 0;
}
