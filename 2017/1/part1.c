#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10000

int main() {
    char* input = malloc(MAX_ * sizeof(char));
    int n = 0;
    char c;

    while ((c = getchar()) != '\n') {
        input[n++] = c;
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (input[i] == input[(i + 1)%n]) {
            res+= input[i] - '0';
        }
    }

    printf("%d\n", res);
    
    return 0;
}
