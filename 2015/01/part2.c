#include <stdio.h>
#include <stdlib.h>

int main() {
    char c;
    int floor = 0;
    int pos = 1;
    while ((c = getchar()) != '\n') {
        switch (c) {
            case '(':
                floor++;
                break;
            case ')':
                floor--;
                break;
        }
        if (floor == -1) {
            printf("%d\n", pos);
            break;
        }
        pos++;

    }

    printf("%d\n", floor);
}

