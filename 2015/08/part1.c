#include <stdio.h>
#include <stdlib.h>

int n_literal(char* line) {
    int total = 0;
    int i = 0;
    while (line[i] != '\n') {
        total++;
        i++;
    }
    return total;
}

int n_memory(char* line) {
    int total = -2;
    int i = 0;
    while (line[i] != '\n') {
        total++;
        if (line[i] == '\\') {
            i++;
            if (line[i] == 'x') {
                i += 2;
            }
        }
        i++;
    }
    return total;
}

int main() {
    char* line = malloc(50 * sizeof(char));
    int total = 0;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);

        fgets(line, 50, stdin);
        total += n_literal(line) - n_memory(line);
    }

    printf("%d\n", total);
    return 0;
}
