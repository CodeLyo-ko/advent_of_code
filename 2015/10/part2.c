#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void look_and_say(char* input, char* output) {
    int k1, k2;
    k1 = k2 = 0;
    int n = 0;


    while (input[k1] != '\0') {
        n = 1;
        k1++;
        while (input[k1] == input[k1 -1]) {
            n++;
            k1++;
        }
        output[k2] = n + '0';
        k2++;
        output[k2] = input[k1 - 1];
        k2++;
    }

    output[k2] = '\0';

}


int main() {
    char* input = malloc(INT_MAX * sizeof(char));
    input = "3113322113";

    char* output = malloc(INT_MAX * sizeof(char));

    for (int i = 0; i < 50; i++) {
        look_and_say(input, output);
        input = strdup(output);
    }

    printf("%d\n", strlen(input));
    return 0;
}
