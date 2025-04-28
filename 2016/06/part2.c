#include <stdio.h>
#include <stdlib.h>
#define MAX_LETTERS 10

void add_frequencies(int** frequencies, char* line) {
    for (int i = 0; line[i] != '\n'; i++) {
        frequencies[i][line[i] - 'a']++;
    }
}

char less_frequent(int* frequencies) {
    int min = 500;
    char letter = '\0';
    
    for (int i = 0; i < 26; i++){
        if (frequencies[i] != 0 && frequencies[i] < min) {
            min = frequencies[i];
            letter = i + 'a';
        }
    }
    return letter;
}

int main() {
    int** frequencies = malloc(MAX_LETTERS * sizeof(int*));
    for (int i = 0; i < MAX_LETTERS; i++) {
        frequencies[i] = calloc(26, sizeof(int));
    }
    
    char* line = malloc(MAX_LETTERS * sizeof(char));
    while(fgets(line, MAX_LETTERS, stdin)){
        add_frequencies(frequencies, line);
    }
    free(line);


    for (int i = 0; i < MAX_LETTERS; i++) {
        printf("%c", less_frequent(frequencies[i]));
    }

    return 0;
}
