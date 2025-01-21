#include <stdio.h>
#include <stdlib.h>

int main() {
    char c;
    int floor = 0;
    while ((c = getchar()) != '\n') {
        switch (c) {
            case '(':
                floor++;
                break;
            case ')':
                floor--;
                break;
        }
    }

    printf("%d\n", floor);
}
