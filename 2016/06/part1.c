#include <stdio.h>
#include <stdlib.h>
#define MAX_LETTERS 10

void add_frequencies(int** frequencies, char* line) {
    for (int i = 0; line[i] != '\n'; i++) {
        frequencies[i][line[i] - 'a']++;
    }
}

char most_frequent(int* frequencies) {
    int max = 0;
    char letter = '\0';
    
    for (int i = 0; i < 26; i++){
        if (frequencies[i] > max) {
            max = frequencies[i];
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
        printf("%c", most_frequent(frequencies[i]));
    }

    return 0;
}
